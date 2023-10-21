/**
 * @file FileHandler.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief This file defines the FileHandler class, which provides utilities for
 * handling files and directories.
 * @version 1.0
 * @date 2023-10-21
 *
 * @copyright (c) 2023 Pedro Lucas
 */

#ifndef FILE_HANDLER_HPP_
#define FILE_HANDLER_HPP_

#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string_view>
#include "ExplorerFunctions.hpp"

/**
 * @brief Namespace 'ext' for external utilities and extensions.
 */
namespace ext {
namespace fs = std::filesystem;

/**
 * @class FileHandler
 * @brief A class for handling files and providing information about them.
 *
 * This class extends the functionality of std::filesystem::path and provides
 * methods to determine file type, check for specific file types, manipulate
 * files, and retrieve file information.
 */
class FileHandler : public fs::path {
 private:
   std::ios_base::openmode m_mode;

   FileHandler &assign(fs::path const &path_) {
      static_cast<fs::path &>(*this) = path_;
      return *this;
   }

 public:
   /**
    * @enum RegularType
    * @brief Enumerates specific regular file types.
    */
   enum RegularType {
      DOCUMENT,   ///< Document file.
      SHEET,      ///< Spreadsheet file.
      SLIDE,      ///< Presentation slide file.
      IMAGE,      ///< Image file.
      SOUND,      ///< Sound file.
      VIDEO,      ///< Video file.
      COMPACT,    ///< Archive or compressed file.
      CODE,       ///< Source code file.
      DATA,       ///< Data file.
      BOOK,       ///< E-book file.
      FONT,       ///< Font file.
      EXECUTABLE, ///< Executable file.
      UNCHARTED,  ///< Unknown or unclassified regular file type.
   };

   /**
    * @brief Default constructor for a FileHandler object.
    */
   FileHandler() {}

   /**
    * @brief Constructs a FileHandler object from a path representation.
    * @param path_ The path to a file, which can be a C-string, std::string, or
    * std::string_view.
    */
   FileHandler(fs::path const &path_,
               std::ios_base::openmode mode_ = std::ios::out) {
      if (fs::is_regular_file(path_) || !fs::exists(path_)) {
         assign(path_);
         m_mode = mode_;
      } else {
         throw std::invalid_argument(
             "Cannot create a FileHandler from a directory path.");
      }
   }

   FileHandler &operator=(fs::path const &path_) {
      if (fs::is_regular_file(path_) || !fs::exists(path_)) {
         assign(path_);
         m_mode = std::ios::out;
      } else {
         throw std::invalid_argument(
             "Cannot create a FileHandler from a directory path.");
      }

      return *this;
   }

   FileHandler &operator=(FileHandler const &path_) {
      if (fs::is_regular_file(path_) || !fs::exists(path_)) {
         assign(path_);
         m_mode = path_.getMode();
      } else {
         throw std::invalid_argument(
             "Cannot create a FileHandler from a directory path.");
      }

      return *this;
   }

   /**
    * @brief Opens a file by assigning a new path to the FileHandler object.
    * @param path_ The path to the file to open.
    */
   void open(fs::path const &path_,
             std::ios_base::openmode mode_ = std::ios::out) {
      if (fs::is_regular_file(path_) || !fs::exists(path_)) {
         assign(path_);
         m_mode = mode_;
      } else {
         throw std::invalid_argument(
             "Cannot create a FileHandler from a directory path.");
      }
   }

   /**
    * @brief Checks if the file exists.
    * @return True if the file exists, false otherwise.
    */
   bool exists() const { return fs::exists(*this); }

   std::ios_base::openmode getMode() const { return m_mode; }

   /**
    * @brief Check if the file is a document.
    * @return True if the file is a document, false otherwise.
    */
   bool isDocument() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view document_ext[] = {".txt", ".doc", ".docx",
                                         ".odt", ".pdf", ".rtf"};

      for (std::string_view *left{std::begin(document_ext)};
           left != std::end(document_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a spreadsheet.
    * @return True if the file is a spreadsheet, false otherwise.
    */
   bool isSheet() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view sheet_ext[] = {".xls", ".xlsx", ".ods", ".csv"};

      for (std::string_view *left{std::begin(sheet_ext)};
           left != std::end(sheet_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a presentation slide.
    * @return True if the file is a presentation slide, false otherwise.
    */
   bool isSlide() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view slide_ext[] = {".ppt", ".pptx", ".odp"};

      for (std::string_view *left{std::begin(slide_ext)};
           left != std::end(slide_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is an image.
    * @return True if the file is an image, false otherwise.
    */
   bool isImage() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view image_ext[] = {".jpg", ".jpeg", ".png",  ".gif",
                                      ".bmp", ".tif",  ".tiff", ".ppm"};

      for (std::string_view *left{std::begin(image_ext)};
           left != std::end(image_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a sound file.
    * @return True if the file is a sound file, false otherwise.
    */
   bool isSound() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view sound_ext[] = {".mp3", ".wav", ".flac", ".ogg", ".aac"};

      for (std::string_view *left{std::begin(sound_ext)};
           left != std::end(sound_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a video file.
    * @return True if the file is a video file, false otherwise.
    */
   bool isVideo() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view video_ext[] = {".mp4", ".avi", ".mkv",
                                      ".mov", ".wmv", ".flv"};

      for (std::string_view *left{std::begin(video_ext)};
           left != std::end(video_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a compact or archive file.
    * @return True if the file is a compact or archive file, false otherwise.
    */
   bool isCompact() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view compact_ext[] = {".zip", ".rar", ".tar.gz",
                                        ".tar", ".gz",  ".7z"};

      for (std::string_view *left{std::begin(compact_ext)};
           left != std::end(compact_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Check if the file is a source code file.
    * @return True if the file is a source code file, false otherwise.
    */
   bool isCode() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view code_ext[] = {".c",    ".cpp", ".cxx",  ".h",
                                     ".hpp",  ".hxx", ".java", ".py",
                                     ".html", ".css", ".js"};

      for (std::string_view *left{std::begin(code_ext)};
           left != std::end(code_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Checks if the file is a data file.
    * @return True if the file is a data file, false otherwise.
    */
   bool isData() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view data_ext[] = {".xml", ".json", ".sqlite", ".mysql",
                                     ".db"};

      for (std::string_view *left{std::begin(data_ext)};
           left != std::end(data_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Checks if the file is a book (e-book) file.
    * @return True if the file is a book file, false otherwise.
    */
   bool isBook() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view book_ext[] = {".epub", ".mobi", ".azw"};

      for (std::string_view *left{std::begin(book_ext)};
           left != std::end(book_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Checks if the file is a font file.
    * @return True if the file is a font file, false otherwise.
    */
   bool isFont() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view font_ext[] = {".ttf", ".otf", ".woff"};

      for (std::string_view *left{std::begin(font_ext)};
           left != std::end(font_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Checks if the file is an executable file.
    * @return True if the file is an executable file, false otherwise.
    */
   bool isExecutable() const {
      if (!exists()) {
         return false;
      }

      fs::path ext{(*this).extension()};

      std::string_view executable_ext[] = {
          "", ".exe", ".dll", ".sys", ".so", ".app", ".dylib", ".apk", ".out"};

      for (std::string_view *left{std::begin(executable_ext)};
           left != std::end(executable_ext); ++left) {
         if (ext == *left) {
            return true;
         }
      }

      return false;
   }

   /**
    * @brief Get the specific RegularType of the file.
    * @return The RegularType of the file, or UNCHARTED if the file is not
    * regular.
    */
   RegularType getRegularType() const {
      if (isDocument()) {
         return DOCUMENT;
      } else if (isSheet()) {
         return SHEET;
      } else if (isSlide()) {
         return SLIDE;
      } else if (isImage()) {
         return IMAGE;
      } else if (isSound()) {
         return SOUND;
      } else if (isVideo()) {
         return VIDEO;
      } else if (isCompact()) {
         return COMPACT;
      } else if (isCode()) {
         return CODE;
      } else if (isData()) {
         return DATA;
      } else if (isFont()) {
         return FONT;
      } else if (isBook()) {
         return BOOK;
      } else if (isExecutable()) {
         return EXECUTABLE;
      }

      return UNCHARTED;
   }

   /**
    * @brief Get the base name of the file (file name without extension).
    * @return The base name of the file.
    */
   std::string basename() const {
      std::string name(this->filename());
      std::string ext(this->extension());

      return name.erase(name.size() - ext.size());
   }

   /**
    * @brief Get the directory path of the file.
    * @return The directory path of the file.
    */
   std::string directoryPath() const {
      std::string full{*this};
      std::string name{this->filename()};

      return full.erase(full.size() - name.size());
   }

   /**
    * @brief Get the size of the file in bytes.
    * @return The size of the file in bytes.
    */
   size_t size() const { return fs::file_size(*this); }

   /**
    * @brief Get the modification time of the file.
    * @return The modification time of the file as a fs::file_time_type.
    */
   fs::file_time_type modificationTime() const {
      return fs::last_write_time(*this);
   }

   /**
    * @brief Set the modification time of the file.
    * @param new_time The new modification time as a fs::file_time_type.
    */
   void modificationTime(fs::file_time_type new_time) {
      fs::last_write_time(*this, new_time);
   }

   /**
    * @brief Remove the file from the filesystem.
    */
   void remove() { fs::remove(*this); }

   /**
    * @brief Rename the file.
    * @param new_name_ A new name for the file.
    * @return True if the file was successfully renamed, false if a file with
    * the new name already exists.
    */
   bool rename(std::string_view const &new_name_) {
      if (fs::exists(new_name_)) {
         return false;
      }

      fs::rename(*this, new_name_);
      *this = {new_name_, m_mode};

      return true;
   }

   /**
    * @brief Write data to the file.
    * @param input_ The data to be written to the file.
    * @param mode_ The open mode for the file (default is std::ios::out).
    */
   void write(std::string const &input_,
              std::ios_base::openmode mode_ = std::ios::out) {
      if (!exists()) {
         return;
      }

      std::ofstream file(*this, mode_);

      if (!file) {
         return;
      }

      char *str = new char[input_.size()];
      size_t i = 0;
      for (char a : input_) {
         str[i++] = a;
      }

      file.write(str, input_.size());
      delete[] str;
      file.close();
   }

   /**
    * @brief Read data from the file.
    * @param output_ The data read from the file.
    * @param mode_ The open mode for the file (default is std::ios::in).
    */
   void read(std::string &output_,
             std::ios_base::openmode mode_ = std::ios_base::in) {
      if (!exists()) {
         return;
      }

      std::ifstream file(*this, mode_);

      if (!file) {
         return;
      }

      file.seekg(0, std::ios::end);
      size_t output_size = file.tellg();
      file.seekg(0, std::ios::beg);

      char *str = new char[output_size];

      file.read(str, output_size);

      for (size_t i = 0; i < output_size; i++) {
         output_.push_back(str[i]);
      }

      delete[] str;
      file.close();
   }
};
} // namespace ext

#endif /// FILE_HANDLER_HPP_