/**
 * @file vmenu.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Vertical menu base class for linux.
 * @version 1.0
 * @date 2023-10-20
 *
 * This header file defines the vmenu class, which is a subclass of the menu
 * class. It provides functionality for rendering and interacting with a
 * vertical menu using the ncurses library.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef VMENU_HPP_
#define VMENU_HPP_

#include "menu.hpp"

namespace ext {

class vmenu : public menu {
 public:
   /**
    * @brief Constructs a vertical menu with a title and a list of options.
    *
    * @param title_ Title of the menu.
    * @param list_  List of menu options as a pair of (reference, label).
    */
   vmenu(std::string title_ = "",
         std::initializer_list<std::pair<int, std::string>> list_ = {})
       : menu(title_, list_) {}

   /**
    * @brief Constructs a vertical menu with a list of options and no title.
    *
    * @param list_ List of menu options as a pair of (reference, label).
    */
   vmenu(std::initializer_list<std::pair<int, std::string>> list_)
       : menu(list_) {}

   /**
    * @brief Renders the vertical menu on the screen.
    *
    * This method clears the screen, displays the menu title, highlights the
    * selected option, and shows instructions for navigation and selection.
    */
   void render() const {
      clear();

      if (!this->get_title().empty()) {
         printw("%s\n", this->get_title().c_str());
      }

      auto opt{this->get_options()};

      for (size_t index{0}; index != opt.size(); ++index) {
         if (index == this->get_index()) {
            attron(A_REVERSE); // Enable reverse video mode for highlighting.
         }

         printw("%s", opt[index].second.c_str());

         if (index == this->get_index()) {
            attroff(A_REVERSE); // Disable reverse video mode.
         }

         printw("\n");
      }

      printw("\nPress UP or DOWN to move and ENTER to select!");

      refresh();
   }

   /**
    * @brief Processes user input for navigation and selection.
    *
    * This method captures user input and responds to ARROW keys (UP and DOWN)
    * and ENTER keys to navigate through menu options and select an option.
    */
   void process() {
      int key = getch();

      switch (key) {
      case KEY_DOWN:
         add_index();
         break;
      case KEY_UP:
         sub_index();
         break;
      case ENTER:
         select();
         break;
      default:
         break;
      }
   }
};

} // namespace ext

#endif /// VMENU_HPP_
