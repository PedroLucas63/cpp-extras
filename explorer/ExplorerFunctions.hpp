#ifndef EXPLORER_FUNCTIONS_HPP_
#define EXPLORER_FUNCTIONS_HPP_

#include <filesystem>
#include <string>

namespace ext {
namespace fs = std::filesystem;

/**
 * @brief Get the file's permissions as a string.
 * @return A string representing the file's permissions in the form
 * "rwxrwxrwx".
 */
std::string permissions(fs::path const &path_) {
   std::string perms_str;

   using std::filesystem::perms;
   perms p{fs::status(path_).permissions()};

   auto show = [=](std::string &str, char op, perms perm) {
      str.push_back(perms::none == (perm & p) ? '-' : op);
   };

   show(perms_str, 'r', perms::owner_read);
   show(perms_str, 'w', perms::owner_write);
   show(perms_str, 'x', perms::owner_exec);
   show(perms_str, 'r', perms::group_read);
   show(perms_str, 'w', perms::group_write);
   show(perms_str, 'x', perms::group_exec);
   show(perms_str, 'r', perms::others_read);
   show(perms_str, 'w', perms::others_write);
   show(perms_str, 'x', perms::others_exec);

   return perms_str;
}
} // namespace ext

#endif /// EXPLORER_FUNCTIONS_HPP_