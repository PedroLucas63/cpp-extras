#ifndef EXPLORER_HPP_
#define EXPLORER_HPP_

#include "ExplorerFunctions.hpp"
#include "FileHandler.hpp"
#include "List.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

namespace ext {
namespace fs = std::filesystem;

class Explorer : public fs::directory_entry {
 private:
   Explorer &assign(fs::path const &path_) {
      static_cast<fs::directory_entry &>(*this) = fs::directory_entry(path_);

      return *this;
   }

 public:
   Explorer() {}
   Explorer(fs::path const &path_) {
      if (fs::is_directory(path_) || !fs::exists(path_)) {
         assign(path_);
      } else {
         throw std::invalid_argument(
             "Cannot create a Explorer from a file path.");
      }
   }

   Explorer &operator=(fs::path const &path_) {
      if (fs::is_directory(path_) || !fs::exists(path_)) {
         assign(path_);
      } else {
         throw std::invalid_argument(
             "Cannot create a Explorer from a file path.");
      }

      return *this;
   }

   void open(fs::path const &path_) {
      if (fs::is_directory(path_) || !fs::exists(path_)) {
         assign(path_);
      } else {
         throw std::invalid_argument(
             "Cannot create a Explorer from a file path.");
      }
   }

   /**
    * @brief Checks if the file exists.
    * @return True if the file exists, false otherwise.
    */
   bool exists() const { return fs::exists(*this); }

   bool create() const {
      if (exists()) {
         return false;
      }

      fs::create_directory(*this);
      return true;
   }

   void remove() { fs::remove_all(*this); }

   bool rename(Explorer const &new_folder_) {
      if (new_folder_.exists()) {
         return false;
      }

      fs::rename(*this, new_folder_);
      return true;
   }

   bool copy(Explorer const& destiny_) {
      if (destiny_.exists()) {
         return false;
      }

      fs::copy(*this, destiny_);
      return true;
   }

   std::uintmax_t capacity() const {
      if (!this->exists()) {
         return 0;
      }

      return fs::space(*this).capacity;
   }

   std::uintmax_t free() const {
      if (!this->exists()) {
         return 0;
      }

      return fs::space(*this).free;
   }

   std::uintmax_t available() const {
      if (!this->exists()) {
         return 0;
      }

      return fs::space(*this).available;
   }

   std::string tree(size_t depth_ = 0) const {
      if (!exists()) {
         return std::string();
      }

      std::ostringstream oss;

      oss << "\33[34m" << fs::path(*this).filename().generic_string()
          << "\33[0m\n";

      std::string bars;

      for (size_t quant { 0 }; quant != depth_ + 1; ++quant) {
         bars += "| ";
      }

      for (auto children : fs::directory_iterator(*this)) {
         oss << bars;

         if (fs::is_directory(children)) {
            Explorer e{children};
            oss << e.tree(depth_ + 1);
         } else {
            oss << fs::path(children).filename().generic_string() << "\n";
         }
      }

      return oss.str();
   }

   std::string list() {
      if (!exists()) {
         return std::string();
      }

      std::ostringstream oss;

      for (auto children : fs::directory_iterator(*this)) {
         if (fs::is_directory(children)) {
            oss << "\33[34m" << fs::path(children).filename().generic_string()
                << "\33[0m\n";
         } else {
            oss << fs::path(children).filename().generic_string() << "\n";
         }
      }

      return oss.str();
   }

   std::string listPermissions() {
      if (!exists()) {
         return std::string();
      }

      std::ostringstream oss;

      for (auto children : fs::directory_iterator(*this)) {
         oss << permissions(children) << " ";

         if (fs::is_directory(children)) {
            oss << "\33[34m" << fs::path(children).filename().generic_string()
                << "\33[0m\n";
         } else {
            oss << fs::path(children).filename().generic_string() << "\n";
         }
      }

      return oss.str();
   }

   List getChildrens() const {
      List list;

      for (auto children : fs::recursive_directory_iterator(*this)) {
         list.pushBack(children);
      }

      return list;
   }

   List getImediateChildrens() const {
      List list;

      for (auto children : fs::directory_iterator(*this)) {
         list.pushBack(children);
      }

      return list;
   }

   bool createDirectory(Explorer const &folder_) const {
      if (folder_.exists()) {
         return false;
      }

      fs::path root = fs::path(*this);
      fs::path dir = fs::path(folder_);
      fs::path folder = root.generic_string() + "/" + dir.generic_string();
      fs::create_directory(folder);
      return true;
   }

   bool renameDirectory(Explorer &folder_, Explorer const &new_folder_) const {
      if (new_folder_.exists()) {
         return false;
      }

      folder_.rename(new_folder_);
      return true;
   }

   bool copyDirectory(Explorer const &folder_, Explorer const &destiny_) const {
      if (destiny_.exists()) {
         return false;
      }

      fs::copy(folder_, destiny_);
      return true;
   }

   bool createFile(FileHandler const &file_) const {
      if (file_.exists()) {
         return false;
      }

      fs::path root = fs::path(*this);
      fs::path file_path = root.generic_string() + "/" + file_.generic_string();

      std::ofstream file{file_path.generic_string(), std::ios::out | file_.getMode()};
      file.close();

      return true;
   }

   bool copyFile(FileHandler const &file_, FileHandler const &destiny_) const {
      if (destiny_.exists()) {
         return false;
      }

      fs::copy_file(file_, destiny_);
      return true;
   }
};
} // namespace ext

#endif /// EXPLORER_HPP_