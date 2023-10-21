#ifndef EXPLORER_LIST_HPP_
#define EXPLORER_LIST_HPP_

#include <filesystem>
#include <stdexcept>

namespace ext {
namespace fs = std::filesystem;

class List {
 private:
   fs::path *m_files;
   size_t m_files_capacity;
   size_t m_files_size;
   fs::path *m_folders;
   size_t m_folders_capacity;
   size_t m_folders_size;

   void pushBackFiles(fs::path const &file_) {
      if (fullFiles()) {
         reserveFiles(m_files_capacity == 0 ? 1 : 2 * m_files_capacity);
      }

      m_files[m_files_size++] = file_;
   }

   void pushBackFolders(fs::path const &folder_) {
      if (fullFolders()) {
         reserveFolders(m_folders_capacity == 0 ? 1 : 2 * m_folders_capacity);
      }

      m_folders[m_folders_size++] = folder_;
   }

 public:
   List()
       : m_files_capacity(0), m_files_size(0), m_folders_capacity(0),
         m_folders_size(0) {
      m_files = new fs::path[m_files_capacity];
      m_folders = new fs::path[m_folders_capacity];
   };

   List(List const &other_)
       : m_files_capacity(other_.getFilesCapacity()),
         m_files_size(other_.getFilesSize()),
         m_folders_capacity(other_.getFoldersCapacity()),
         m_folders_size(other_.getFoldersSize()) {
      m_files = new fs::path[m_files_capacity];

      for (size_t index{0}; index != m_files_size; ++index) {
         m_files[index] = other_.atFiles(index);
      }

      m_folders = new fs::path[m_folders_capacity];

      for (size_t index{0}; index != m_folders_size; ++index) {
         m_folders[index] = other_.atFolders(index);
      }
   }

   List &operator=(List const &rhs_) {
      m_files_capacity = rhs_.getFilesCapacity();
      m_files_size = rhs_.getFilesSize();
      m_folders_capacity = rhs_.getFoldersCapacity();
      m_folders_size = rhs_.getFoldersSize();
      delete[] m_files;
      m_files = new fs::path[m_files_capacity];

      for (size_t index{0}; index != m_files_size; ++index) {
         m_files[index] = rhs_.atFiles(index);
      }

      delete[] m_folders;
      m_folders = new fs::path[m_folders_capacity];

      for (size_t index{0}; index != m_folders_size; ++index) {
         m_folders[index] = rhs_.atFolders(index);
      }

      return *this;;;
   }

   ~List() {
      delete[] m_files;
      delete[] m_folders;
   }

   fs::path &atFiles(size_t index_) const {
      if (index_ >= m_files_size) {
         throw std::out_of_range("The index is greater than the size.");
      }

      return m_files[index_];
   }

   fs::path &atFolders(size_t index_) const {
      if (index_ >= m_folders_size) {
         throw std::out_of_range("The index is greater than the size.");
      }

      return m_folders[index_];
   }

   size_t getFilesCapacity() const { return m_files_capacity; }
   size_t getFilesSize() const { return m_files_size; }
   size_t getFoldersCapacity() const { return m_folders_capacity; }
   size_t getFoldersSize() const { return m_folders_size; }

   bool fullFiles() const { return m_files_capacity == m_files_size; }
   bool emptyFiles() const { return m_files_size == 0; }
   bool fullFolders() const { return m_folders_capacity == m_folders_size; }
   bool emptyFolders() const { return m_folders_size == 0; }

   fs::path *beginFiles() { return m_files; }
   fs::path *endFiles() { return m_files + m_files_size; }
   fs::path *beginFolders() { return m_folders; }
   fs::path *endFolders() { return m_folders + m_folders_size; }

   void reserveFiles(size_t new_capacity_) {
      if (new_capacity_ <= m_files_capacity) {
         return;
      }

      fs::path *temp = new fs::path[new_capacity_];

      for (size_t index{0}; index != m_files_size; ++index) {
         temp[index] = m_files[index];
      }

      m_files_capacity = new_capacity_;
      delete[] m_files;
      m_files = temp;
   }

   void reserveFolders(size_t new_capacity_) {
      if (new_capacity_ <= m_folders_capacity) {
         return;
      }

      fs::path *temp = new fs::path[new_capacity_];

      for (size_t index{0}; index != m_folders_size; ++index) {
         temp[index] = m_folders[index];
      }

      m_folders_capacity = new_capacity_;
      delete[] m_folders;
      m_folders = temp;
   }

   void pushBack(fs::path const &path_) {
      if (fs::is_regular_file(path_)) {
         pushBackFiles(path_);
      } else if (fs::is_directory(path_)) {
         pushBackFolders(path_);
      }
   }
   void popBackFiles() {
      if (!emptyFiles()) {
         --m_files_size;
      }
   }

   void popBackFolders() {
      if (!emptyFolders()) {
         --m_folders_size;
      }
   }
};
} // namespace ext

#endif /// EXPLORER_LIST_HPP_