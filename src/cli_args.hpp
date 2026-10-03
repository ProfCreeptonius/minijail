#ifndef CLI_ARGS_HEADER_GUARD
#define CLI_ARGS_HEADER_GUARD

#include <expected>
#include <filesystem>
#include <string>

namespace MiniJail::Cli {

struct Config {
  std::filesystem::path root;
  std::filesystem::path exe;
};

std::expected<Config, std::string> parse_cli(int argc, char **argv);
} // namespace MiniJail::Cli

#endif // CLI_ARGS_HEADER_GUARD
