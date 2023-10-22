/**
 * @file vmenu.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Vertical menu base class for windows.
 * @version 1.0
 * @date 2023-10-20
 *
 * This header file defines the vmenu class, which is a subclass of the menu
 * class. It provides functionality for rendering and interacting with a
 * vertical menu in a Windows environment.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef VMENU_HPP_
#define VMENU_HPP_

#include "menu.hpp"

namespace ext {

/**
 * @brief Vertical Menu Class
 *
 * The `vmenu` class is a specialized subclass of the menu class, designed to create and manage
 * vertical menus in a Windows environment. It facilitates the rendering of menu options, user
 * navigation, and selection of options within a vertical layout. This class simplifies the
 * development of interactive vertical menus for Windows-based applications.
 *
 * @see menu
 */
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
      system("cls");

      if (!this->get_title().empty()) {
         std::cout << this->get_title() << "\n";
      }

      auto opt{this->get_options()};

      for (size_t index{0}; index != opt.size(); ++index) {
         if (index == this->get_index()) {
            std::cout
                << "\33[7m"; // Enable reverse video mode for highlighting.
         }

         std::cout << opt[index].second;

         if (index == this->get_index()) {
            std::cout << "\33[0m"; // Disable reverse video mode.
         }

         std::cout << "\n";
      }

      std::cout << "\nPress UP or DOWN to move and ENTER to select!";
   }

   /**
    * @brief Processes user input for navigation and selection.
    *
    * This method captures user input and responds to ARROW keys (UP and DOWN)
    * and ENTER keys to navigate through menu options and select an option.
    */
   void process() {
      int key = getch();
      int key_aux;

      switch (key) {
      case ARROWS:
         key_aux = getch();

         switch (key_aux) {
         case DOWN:
            add_index();
            break;
         case UP:
            sub_index();
            break;
         default:
            break;
         }
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
