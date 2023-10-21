#include "../explorer/Explorer.hpp"
#include <cassert>

void TestExplorer() {
   // Test creating an Explorer with an existing directory
   ext::Explorer explorer_exists{"source"};
   assert(explorer_exists.exists());

   // Test creating an Explorer with a non-existing directory
   ext::Explorer explorer_nexists{"non_existing_directory"};
   assert(!explorer_nexists.exists());

   // Test creating an Explorer with a file path (should throw an exception)
   bool exception_thrown = false;
   try {
      ext::Explorer explorer_file{"source/files/file_out.txt"};
   } catch (const std::invalid_argument &e) {
      exception_thrown = true;
   }
   assert(exception_thrown);

   // Test creating an Explorer with an existing directory and opening another
   // one
   ext::Explorer explorer{"source"};
   explorer.open("source/files");
   assert(explorer.exists());

   // Test creating an Explorer with a non-existing directory and opening
   // another one
   ext::Explorer explorer2{"non_existing_directory"};
   explorer2.open("source");
   assert(explorer2.exists());
}

void TestCreateRemoveRename() {
   // Test creating a new directory
   ext::Explorer new_dir{"source/new_directory"};
   bool create_result = new_dir.create();
   assert(create_result);
   assert(new_dir.exists());

   // Test removing the directory
   new_dir.remove();
   assert(!new_dir.exists());

   // Test renaming a directory
   ext::Explorer old_folder{"source/old_folder"};
   old_folder.create();
   ext::Explorer new_folder{"source/new_folder"};
   bool rename_result = old_folder.rename(new_folder);
   assert(rename_result);
   assert(!old_folder.exists());
   assert(new_folder.exists());
}

void TestCapacityFreeAvailable() {
   ext::Explorer explorer{"source"};
   std::uintmax_t capacity = explorer.capacity();
   std::uintmax_t free = explorer.free();
   std::uintmax_t available = explorer.available();
   assert(capacity > 0);
   assert(free > 0);
   assert(available > 0);
}

void TestCreateFile() {
   // Test creating a new file
   ext::Explorer explorer{"source"};
   ext::FileHandler new_file{"source/new_file.txt"};
   bool create_result = explorer.createFile(new_file);
   assert(create_result);
   assert(new_file.exists());
}

void TestCopyFile() {
   // Test copying a file
   ext::FileHandler source_file{"source/files/file_out.txt"};
   ext::FileHandler destination_file{"source/copy_of_file_out.txt"};

   ext::Explorer explorer{"source"};
   bool copy_result = explorer.copy(source_file, destination_file);
   assert(copy_result);
   assert(destination_file.exists());

   // Clean up: remove the copied file
   destination_file.remove();
   assert(!destination_file.exists());
}

int main() {
   std::cout << "Running tests...\n";

   // Run Explorer tests
   TestExplorer();
   TestCreateRemoveRename();
   TestCapacityFreeAvailable();
   // Run file manipulation tests
   TestCreateFile();
   TestCopyFile();

   std::cout << "All tests passed!\n";

   return 0;
}
