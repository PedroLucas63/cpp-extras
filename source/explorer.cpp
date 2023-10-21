#include <iostream>
#include <cassert>
#include "../explorer/FileHandler.hpp"

void TestConstructor() {
    // Test constructor with an existing regular file
    ext::FileHandler file_out_exists{"source/files/file_out.txt"};
    assert(file_out_exists.exists());

    // Test constructor with a non-existing file
    ext::FileHandler file_nexists{"source/files/non_existing_file.txt"};
    assert(!file_nexists.exists());
}

void TestCopyConstructor() {
    // Test copy constructor with an existing regular file
    ext::FileHandler file_out_exists{"source/files/file_out.txt"};
    ext::FileHandler file_const_copy{file_out_exists};
    assert(file_const_copy.exists());

    // Test copy constructor with a non-existing file
    ext::FileHandler file_nexists{"source/files/non_existing_file.txt"};
    ext::FileHandler file_const_copy2 = file_nexists;
    assert(!file_const_copy2.exists());
}

void TestOpen() {
    // Test opening an existing regular file
    ext::FileHandler file_no_data;
    file_no_data.open("source/files/new_file.cpp");
    assert(file_no_data.exists());

    // Test opening a non-existing file
    ext::FileHandler file_no_data2;
    file_no_data2.open("source/files/non_existing_file2.txt");
    assert(!file_no_data2.exists());

    // Test opening with mode
    ext::FileHandler file_no_data3;
    file_no_data3.open("source/files/new_file3.cpp", std::ios::binary);
    assert(file_no_data3.exists());
}

void TestType() {
    // Test various file types
    ext::FileHandler file_doc { "source/files/file.doc" };
    assert(file_doc.getRegularType() == ext::FileHandler::DOCUMENT);

    ext::FileHandler file_exe { "source/files/file.exe" };
    assert(file_exe.getRegularType() == ext::FileHandler::EXECUTABLE);

    ext::FileHandler file_zip { "source/files/file.zip" };
    assert(file_zip.getRegularType() == ext::FileHandler::COMPACT);
}

void TestBasename() {
    // Test getting the basename
    ext::FileHandler file_example { "source/files/example.txt" };
    assert(file_example.basename() == "example");
}

void TestDirectoryPath() {
    // Test getting the directory path
    ext::FileHandler file_example { "source/files/example.txt" };
    assert(file_example.directoryPath() == "source/files/");
}

void TestSize() {
    // Test getting the size of a file
    ext::FileHandler file_out_exists{"source/files/file_out.txt"};
    size_t expected_size = std::filesystem::file_size("source/files/file_out.txt");
    assert(file_out_exists.size() == expected_size);
}

void TestRemove() {
    // Test removing a file
    ext::FileHandler file_to_remove{"source/files/to_remove.txt"};
    std::ofstream file(file_to_remove.generic_string());
    file.close();
    assert(file_to_remove.exists());

    file_to_remove.remove();
    assert(!file_to_remove.exists());
}

void TestRename() {
    // Test renaming a file
    ext::FileHandler file_to_rename{"source/files/to_rename.txt"};
    std::ofstream file(file_to_rename.generic_string());
    file.close();
    assert(file_to_rename.exists());

    bool rename_result = file_to_rename.rename("source/files/renamed.txt");
    assert(rename_result);
    assert(file_to_rename.exists());

    ext::FileHandler renamed_file{"source/files/renamed.txt"};
    assert(renamed_file.exists());
}

void TestWriteAndRead() {
    // Test writing and reading from a file
    ext::FileHandler file_for_io{"source/files/io_test.txt"};

    std::string data_to_write = "Hello, World!";
    file_for_io.write(data_to_write);
    
    std::string data_read;
    file_for_io.read(data_read);

    assert(data_read == data_to_write);
}

int main() {
    std::cout << "Running tests...\n";

    TestConstructor();
    TestCopyConstructor();
    TestOpen();
    TestType();
    TestBasename();
    TestDirectoryPath();
    TestSize();
    TestRemove();
    TestRename();
    TestWriteAndRead();

    std::cout << "All tests passed!\n";

    return 0;
}
