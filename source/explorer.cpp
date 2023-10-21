#include "../explorer/Explorer.hpp"
#include <iostream>

int main() {
   std::cout << "\n[========[CONSTRUCTOR]========]\n";
   ext::FileHandler file_out_exists {"files/file_out.txt"};
   ext::FileHandler file_bin_nexists {"files/file_bin.txt"};
   ext::FileHandler file_nexists {"files/file.txt"};
   std::cout << file_out_exists << "\n";
   std::cout << file_bin_nexists << "\n";
   std::cout << file_nexists << "\n";
}