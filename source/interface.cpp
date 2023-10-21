#include "../interface/interface.hpp"
#include <memory>

int MainMenu() {
   std::unique_ptr<ext::vmenu> main_menu{
       std::make_unique<ext::vmenu>("Main menu!")};
   main_menu->insert_option(1, "Play");
   main_menu->insert_option(2, "About");
   main_menu->insert_option(-1, "Exit");

   while (!main_menu->exit()) {
      main_menu->render();
      main_menu->process();
   }

   return main_menu->get_selected();
}

int PlayMenu() {
   std::unique_ptr<ext::hmenu> play_menu{
       std::make_unique<ext::hmenu>("Play menu!")};
   play_menu->insert_option(2, "About");
   play_menu->insert_option(0, "Return");

   while (!play_menu->exit()) {
      play_menu->render();
      play_menu->process();
   }

   return play_menu->get_selected();
}

int AboutMenu() {
   std::unique_ptr<ext::hmenu> about_menu{
       std::make_unique<ext::hmenu>("About menu!")};
   about_menu->insert_option(0, "Return");

   while (!about_menu->exit()) {
      about_menu->render();
      about_menu->process();
   }

   return about_menu->get_selected();
}

int main() {
   int choice = 0;
   while (choice != -1) {
      if (choice == 0) {
         choice = MainMenu();
      } else if (choice == 1) {
         choice = PlayMenu();
      } else {
         choice = AboutMenu();
      }
   }

   return 0;
}