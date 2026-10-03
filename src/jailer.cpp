#include "jailer.hpp"

#include <cstring>
#include <filesystem>
#include <format>
#include <print>
#include <vector>

#include <sys/param.h>
#include <sys/jail.h>
#include <sys/uio.h>
#include <unistd.h>

struct IovecBuilder {
  IovecBuilder() = default;

  IovecBuilder &add(auto &&...str_constructor_args) {
    strings.emplace_back(std::forward<std::string>(str_constructor_args...));
    iovecs.emplace_back(strings.back().data(), strings.back().size() + 1);
    return *this;
  }

  IovecBuilder &add_static_str(const char *cstr) {
    cstrings.push_back(cstr);
    iovecs.emplace_back(reinterpret_cast<void *>(const_cast<char *>(cstr)),
                        std::strlen(cstr) + 1);
    return *this;
  }

  IovecBuilder &add_null() {
    iovecs.emplace_back(nullptr, 0);
    return *this;
  }

  std::vector<struct iovec> &get() { return iovecs; }

private:
  std::vector<std::string> strings;
  std::vector<const char *> cstrings;
  std::vector<struct iovec> iovecs;
};

std::string jailname_from_path(const std::filesystem::path &path) {
  return std::format("minijail_{}", path.filename().c_str());
}

std::expected<void, std::string>
MiniJail::make_jail(const MiniJail::Cli::Config &config) {
  std::string jail_name = jailname_from_path(config.exe);
  auto relative_exe_path = std::filesystem::proximate(config.exe, config.root);
  IovecBuilder builder;
  builder.add_static_str("path")
      .add(config.root.string())
      .add_static_str("name")
      .add(std::move(jail_name));

  int jid = jail_set(builder.get().data(), builder.get().size(),
                     JAIL_CREATE | JAIL_ATTACH);
  if (jid < 0) {
    return std::unexpected{
        std::format("Failed to jail_set: {}, {}", errno, strerror(errno))};
  }
  std::println("Successfully created jail with id: {}", jid);
  int exec_status =
      execl(relative_exe_path.c_str(), relative_exe_path.c_str(), nullptr);
  if (exec_status != 0) {
    std::println("Jail process failed: Cannot execute {}, error: {}, {}",
                 relative_exe_path.c_str(), errno, strerror(errno));
    exit(-1);
  }
}
