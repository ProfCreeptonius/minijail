#include <print>

#include "cli_args.hpp"
#include "jailer.hpp"

auto main(int argc, char *argv[]) -> int {
  using namespace MiniJail;
  auto config = Cli::parse_cli(argc, argv);
  if (!config.has_value()) {
    std::println("Error, bad arguments: {}", config.error());
    return -1;
  }
  auto error = make_jail(config.value());
  if (!error.has_value()) {
    std::println("Error, cannot create jail: {}", error.error());
    return -1;
  }
  return 0;
}
