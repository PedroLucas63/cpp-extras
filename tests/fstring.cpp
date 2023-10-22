#include "../advance/fstring.hpp"
#include <iostream>
#include <vector>

int main() {
   std::cout << "\n[========[CONSTRUCTOR]========]\n";
   ext::fstring str;
   ext::fstring str2(5, 'a');
   ext::fstring str3{str2, 2};
   ext::fstring str4{str2, 1, 4};
   ext::fstring str5{"Olá", 4};
   ext::fstring str6{"Olá pessoas"};
   ext::fstring str7{str6.begin(), str6.begin() + 4};
   ext::fstring str8{str7};

   std::cout << "Fstring 1: \"" << str << "\"\n";
   std::cout << "Fstring 2: \"" << str2 << "\"\n";
   std::cout << "Fstring 3: \"" << str3 << "\"\n";
   std::cout << "Fstring 4: \"" << str4 << "\"\n";
   std::cout << "Fstring 5: \"" << str5 << "\"\n";
   std::cout << "Fstring 6: \"" << str6 << "\"\n";
   std::cout << "Fstring 7: \"" << str7 << "\"\n";
   std::cout << "Fstring 8: \"" << str8 << "\"\n";

   std::cout << "\n[========[TRIM]========]\n";

   ext::fstring not_trim{"       Sejam todos bem vindo ao pais         "};
   ext::fstring ltrim{not_trim};
   ltrim.ltrim();
   ext::fstring rtrim{not_trim};
   rtrim.rtrim();
   ext::fstring trim{not_trim};
   trim.trim();

   std::cout << "Normal: \"" << not_trim << "\"\n";
   std::cout << "Left trim: \"" << ltrim << "\"\n";
   std::cout << "Right trim: \"" << rtrim << "\"\n";
   std::cout << "Trim: \"" << trim << "\"\n";

   std::cout << "\n[========[REPLACE]========]\n";
   ext::fstring not_replace{"Macacos Macaquiando"};
   not_replace.replace_all("Banana", "Banana");
   ext::fstring replace_first{not_replace};
   replace_first.replace_first("Maca", "Banana");
   ext::fstring replace{not_replace};
   replace.replace_all("Maca", "Banana");

   std::cout << "Normal: \"" << not_replace << "\"\n";
   std::cout << "First replace: \"" << replace_first << "\"\n";
   std::cout << "All replace: \"" << replace << "\"\n";
   std::cout << "Not replace: \"" << not_replace << "\"\n";

   std::cout << "\n[========[SPLIT]========]\n";
   ext::fstring split{"Titulo;Texto;Autor1;;;Editora;Versão;;Casa;"};
   std::vector<ext::fstring<char>> tokens;
   std::vector<ext::fstring<char>> tokens_with_empty;
   split.split(tokens, ';');

   std::cout << "Normal: \"" << split << "\"\n";
   std::cout << "Split: ";
   for (auto e : tokens) {
      std::cout << e.quoted() << " ";
   }

   split.split_with_empty(tokens_with_empty, ';');

   std::cout << "\nSplit with empty: ";
   for (auto e : tokens_with_empty) {
      std::cout << e.quoted() << " ";
   }
   std::cout << "\n";

   std::cout << "\n[========[CONTAINS]========]\n";
   ext::fstring text{"Minha querida casa é muito bonita, venha me visitar!"};
   std::cout << "Normal: \"" << text << "\"\n";
   std::cout << "Contains \"casa\": " << (text.contains("casa") ? "Sim" : "Não")
             << "\n";
   std::cout << "Contains \"barata\": "
             << (text.contains("barata") ? "Sim" : "Não") << "\n";
   std::cout << "Contains \"visita\": "
             << (text.contains("visita") ? "Sim" : "Não") << "\n";
   std::cout << "Contains \"querido\": "
             << (text.contains("querido") ? "Sim" : "Não") << "\n";

   std::cout << "\n[========[APPEND]========]\n";
   ext::fstring title;
   std::cout << "Normal: \"" << title << "\"\n";
   title.append(5, "=-=");
   std::cout << "First append: \"" << title << "\"\n";
   title += "Meu título";
   std::cout << "Add title: \"" << title << "\"\n";
   title.append(5, "=-=");
   std::cout << "Second append: \"" << title << "\"\n";

   std::cout << "\n[========[SPLIT AT]========]\n";
   ext::fstring new_text{
       "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque et "
       "magna eget leo dictum dictum ut luctus erat."};
   std::cout << "Normal: \"" << new_text << "\"\n";
   std::cout << "\nSplit at 50: \n";

   ext::fstring copy{new_text};
   while (!copy.empty() != 0) {
      auto returned = copy.split_at(50);
      std::cout << copy << "\n";
      copy = returned;
   }

   std::cout << "\n[========[ALIGN]========]\n";
   ext::fstring new_text2{"Meu cachorro!"};
   ext::fstring left {new_text2};
   ext::fstring center {new_text2};
   ext::fstring right {new_text2};
   ext::fstring justify {new_text2};

   left.align_left(35);
   center.align_center(35);
   right.align_right(35);
   justify.align_justify(35);

   std::cout << "Normal:    \"" << new_text2 << "\"\n";
   std::cout << "\nAlign left with 35 size:     \"" << left << "\" \n";
   std::cout << "Align center with 35 size:   \"" << center << "\" \n";
   std::cout << "Align right with 35 size:    \"" << right << "\" \n";
   std::cout << "Align justify with 35 size:  \"" << justify << "\" \n";

   std::cout << "\n[========[STYLE]========]\n";
   ext::fstring new_text3{"Meu cachorro!"};
   ext::fstring color {new_text2};
   ext::fstring back {new_text2};
   ext::fstring style {new_text2};
   ext::fstring all {new_text2};
   ext::fstring err {new_text2};

   color.color(ext::cfg::bright_green);
   back.background(ext::cbg::cyan);
   style.style(ext::stl::italic);
   all.background(ext::cbg::bright_red);
   all.color(ext::cfg::bright_green);
   all.style(ext::stl::reverse);
   err.color(ext::cbg::bright_magenta);

   std::cout << "Normal:    \"" << new_text3 << "\"\n";
   std::cout << "\nColor:     \"" << color << "\" \n";
   std::cout << "Background:   \"" << back << "\" \n";
   std::cout << "Style:    \"" << style << "\" \n";
   std::cout << "All:  \"" << all << "\" \n";
   std::cout << "None:  \"" << err << "\" \n";
}