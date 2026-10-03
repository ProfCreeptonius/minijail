#include "cli_args.hpp"
#include "path_utils.hpp"
#include <format>

namespace MiniJail::Cli {

std::expected<Config, std::string> parse_cli(int argc, char **argv) {
  using namespace MiniJail;
  if (argc != 3) {
    return std::unexpected<std::string>{
        "Usage: minijail [root] [program].\nNote: If the root does not "
        "contain /libexec/ld-elf.so.1, you cannot run dynamic executables in "
        "the jail."};
  }
  Config result{.root = argv[1], .exe = argv[2]};
  if (!PathUtils::is_contained_in(result.exe, result.root)) {
    return std::unexpected<std::string>{
        std::format("The program is not contained in the filesystem below {}.",
                    result.root.c_str())};
  }
  if (!PathUtils::is_executable(argv[2])) {
    return std::unexpected<std::string>{
        std::format("The program {} is not executable.", result.exe.c_str())};
  }
  return result;
}

} // namespace MiniJail::Cli
