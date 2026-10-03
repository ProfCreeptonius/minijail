#include "path_utils.hpp"
#include <algorithm>
#include <filesystem>

#include <sys/stat.h>
#include <unistd.h>

namespace MiniJail::PathUtils {

// Checks whether path is contained in base, by canonicalizing and checking
// whether the start is the same.
bool is_contained_in(const std::filesystem::path &path,
                     const std::filesystem::path &base) {
  auto path_canonicalized = std::filesystem::weakly_canonical(path);
  auto base_canonicalized = std::filesystem::weakly_canonical(base);
  std::pair mismatch_pair =
      std::mismatch(path_canonicalized.begin(), path_canonicalized.end(),
                    base_canonicalized.begin(), base_canonicalized.end());
  return mismatch_pair.second == base_canonicalized.end();
}

bool is_executable(const char *path) {
  if (access(path, F_OK) != 0)
    return false;
  struct stat stats;
  if (stat(path, &stats) != 0)
    return false;
  if ((stats.st_mode & S_IXUSR) == 0)
    return false;
  return true;
}

} // namespace MiniJail::PathUtils
