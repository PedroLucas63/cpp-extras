#include "../interface/interface.hpp"

int main() {
   ext::vmenu vertical_menu;
   vertical_menu.set_title("\t\tMeu titulo!\n");
   vertical_menu.insert_option(100, "Play");
   vertical_menu.insert_option(200, "Load");
   vertical_menu.insert_option(300, "About");
   vertical_menu.insert_option(400, "Exit");

   while(!vertical_menu.exit()) {
      vertical_menu.render();
      vertical_menu.process();
   }

   return 0;
}