#ifndef PATH_UTILS_HEADER_GUARD
#define PATH_UTILS_HEADER_GUARD

#include <filesystem>

namespace MiniJail::PathUtils {

bool is_contained_in(const std::filesystem::path &path,
                     const std::filesystem::path &base);

bool is_executable(const char *path);

} // namespace MiniJail::PathUtils


#endif // PATH_UTILS_HEADER_GUARD
