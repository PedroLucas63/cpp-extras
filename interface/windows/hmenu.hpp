/**
 * @file hmenu.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Horizontal menu base class for windows.
 * @version 1.0
 * @date 2023-10-20
 *
 * This header file defines the hmenu class, which is a subclass of the menu
 * class. It provides functionality for rendering and interacting with a
 * horizontal menu in a Windows environment.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef HMENU_HPP_
#define HMENU_HPP_

#include "menu.hpp"

/**
 * @brief Namespace 'ext' for external utilities and extensions.
 */
namespace ext {

/**
 * @brief Horizontal Menu Class for Windows
 *
 * The `hmenu` class is a specialized subclass of the menu class, designed for creating and managing horizontal menus in a Windows environment using the ncurses library. It provides functionality for rendering horizontal menu options, user navigation, and selection of options within a horizontal layout.
 *
 * Key Features:
 * - Create horizontal menus with titles and a list of options.
 * - Utilizes the ncurses library for rendering and interaction.
 * - Navigation using arrow keys (LEFT and RIGHT) to highlight options.
 * - Option selection using the ENTER key.
 *
 * The `hmenu` class simplifies the development of interactive horizontal menus in a Windows environment and is suitable for console-based applications.
 *
 * @see menu
 */
class hmenu : public menu {
 public:
   /**
    * @brief Constructs a horizontal menu with a title and a list of options.
    *
    * @param title_ Title of the menu.
    * @param list_  List of menu options as a pair of (reference, label).
    */
   hmenu(std::string title_ = "",
         std::initializer_list<std::pair<int, std::string>> list_ = {})
       : menu(title_, list_) {}

   /**
    * @brief Constructs a horizontal menu with a list of options and no title.
    *
    * @param list_ List of menu options as a pair of (reference, label).
    */
   hmenu(std::initializer_list<std::pair<int, std::string>> list_)
       : menu(list_) {}

   /**
    * @brief Renders the horizontal menu on the screen.
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

         std::cout << "\t";
      }

      std::cout << "\n\nPress UP or DOWN to move and ENTER to select!";
   }

   /**
    * @brief Processes user input for navigation and selection.
    *
    * This method captures user input and responds to ARROW keys (LEFT and
    * RIGHT) and ENTER keys to navigate through menu options and select an
    * option.
    */
   void process() {
      int key = getch();
      int key_aux;

      switch (key) {
      case ARROWS:
         key_aux = getch();

         switch (key_aux) {
         case RIGHT:
            add_index();
            break;
         case LEFT:
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

#endif /// HMENU_HPP_
