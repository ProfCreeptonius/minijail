#ifndef JAILER_HEADER_GUARD
#define JAILER_HEADER_GUARD

#include "cli_args.hpp"
namespace MiniJail {
  std::expected<void, std::string> make_jail(const MiniJail::Cli::Config &config);
}

#endif // JAILER_HEADER_GUARD
