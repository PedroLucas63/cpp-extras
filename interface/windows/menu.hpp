/**
 * @file menu.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Menu base class for windows.
 * @version 1.0
 * @date 2023-10-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

/**
 * @brief Namespace 'ext' for external utilities and extensions.
 */
namespace ext {
inline constexpr short ARROWS{224};  /**< Constant for arrow key input. */
inline constexpr short ENTER{13};    /**< Constant for the Enter key. */
inline constexpr short SPACE{32};    /**< Constant for the Space key. */
inline constexpr short BACKSPACE{8}; /**< Constant for the Backspace key. */
inline constexpr short TAB{9};       /**< Constant for the Tab key. */
inline constexpr short ESC{27};      /**< Constant for the Escape key. */
inline constexpr short UP{72};       /**< Constant for the Up arrow key. */
inline constexpr short DOWN{80};     /**< Constant for the Down arrow key. */
inline constexpr short LEFT{75};     /**< Constant for the Left arrow key. */
inline constexpr short RIGHT{77};    /**< Constant for the Right arrow key. */

class menu {
 private:
   std::string m_title; /**< Title of the menu. */
   std::vector<std::pair<int, std::string>>
       m_options;          /**< List of menu options. */
   size_t m_index_options; /**< Index of the currently selected option. */
   int m_selected;         /**< Index of the selected option. */

 public:
   /**
    * @brief Constructs a menu with a title and a list of options.
    *
    * @param title_ Title of the menu.
    * @param list_  List of menu options as a pair of (reference, label).
    */
   menu(std::string title_ = "",
        std::initializer_list<std::pair<int, std::string>> list_ = {})
       : m_title(title_), m_options(list_), m_index_options(0), m_selected(-1) {
      HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_CURSOR_INFO info;
      info.dwSize = 100;
      info.bVisible = FALSE;
      SetConsoleCursorInfo(consoleHandle, &info);
   }

   /**
    * @brief Constructs a menu with a list of options and no title.
    *
    * @param list_ List of menu options as a pair of (reference, label).
    */
   menu(std::initializer_list<std::pair<int, std::string>> list_ = {})
       : m_options(list_), m_index_options(0), m_selected(-1) {
      HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_CURSOR_INFO info;
      info.dwSize = 100;
      info.bVisible = FALSE;
      SetConsoleCursorInfo(consoleHandle, &info);
   }

   /**
    * @brief Destructor for the menu class.
    *
    * Clears the console screen when the menu is destroyed.
    */
   ~menu() { system("cls"); }

   /**
    * @brief Sets the title of the menu.
    *
    * @param title_ New title for the menu.
    */
   void set_title(std::string title_) { m_title = title_; }

   /**
    * @brief Inserts a new option into the menu.
    *
    * @param reference_ The reference code for the option.
    * @param label_     The label or description for the option.
    */
   void insert_option(int reference_, std::string label_) {
      m_options.push_back(std::make_pair(reference_, label_));
   }

   /**
    * @brief Inserts a new option into the menu using a pair.
    *
    * @param pair_ The option to be inserted as a pair of (reference, label).
    */
   void insert_option(std::pair<int, std::string> pair_) {
      m_options.push_back(pair_);
   }

   /**
    * @brief Increments the index of the currently selected option.
    *
    * @param add Number of positions to advance the index (default is 1).
    */
   void add_index(size_t add = 1) {
      m_index_options = (m_index_options + add) % m_options.size();
   }

   /**
    * @brief Decrements the index of the currently selected option.
    *
    * @param sub Number of positions to move the index back (default is 1).
    */
   void sub_index(size_t sub = 1) {
      m_index_options =
          (m_index_options - sub + m_options.size()) % m_options.size();
   }

   /**
    * @brief Selects the currently highlighted option.
    */
   void select() { m_selected = m_options[m_index_options].first; }

   /**
    * @brief Retrieves the title of the menu.
    *
    * @return The title of the menu.
    */
   std::string get_title() const { return m_title; }

   /**
    * @brief Retrieves the list of menu options.
    *
    * @return The list of menu options.
    */
   std::vector<std::pair<int, std::string>> get_options() const {
      return m_options;
   }

   /**
    * @brief Retrieves the index of the currently selected option.
    *
    * @return The index of the selected option.
    */
   size_t get_index() const { return m_index_options; }

   /**
    * @brief Retrieves the index of the currently selected option.
    *
    * @return The index of the selected option.
    */
   int get_selected() const { return m_selected; }

   /**
    * @brief Checks if an option has been selected (non-negative index).
    *
    * @return True if an option has been selected, false otherwise.
    */
   bool exit() const { return m_selected != -1; }

   /**
    * @brief Resets the menu to its initial state.
    *
    * Sets the current index and selected option to their initial values.
    */
   void reset() {
      m_index_options = 0;
      m_selected = -1;
   }
};
} // namespace ext

#endif /// MENU_HPP_
