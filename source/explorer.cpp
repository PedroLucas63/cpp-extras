#include <iostream>
#include <memory>
#include "../explorer/Explorer.hpp"
#include "../interface/interface.hpp"

int main() {
   ext::Explorer folder("./save");
   ext::List list = folder.getChildrens();
   std::unique_ptr<ext::vmenu> menu = std::make_unique<ext::vmenu>("Select your save file!\n");

   for (size_t index { 0 }; index != list.getFilesSize(); ++index) {
      ext::FileHandler file {list.atFiles(index)};
      if (file.extension() == ".sav") {
         menu->insert_option(index, file.basename());
      }
   }

   menu->insert_option(-1, "0. Return");

   while(!menu->exit()) {
      menu->render();
      menu->process();
   }
   
   int choice = menu->get_selected();
   if (choice != -1) {
      menu.reset();
      std::cout << "O item escolhido foi: " << list.atFiles(choice) << "\n";
   }

   return 0;
}