#include "../cli/Cli.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
   ext::CLI cli;
   cli.addArgument('h', "help");
   cli.addArgumentInteger('x', "x-axis");
   cli.addArgumentFloating('y', "y-axis");
   cli.addArgumentText('t', "title");
   cli.addArgumentInFile('f', "file");
   cli.addArgumentOutFile('o', "out-file");

   cli.parse(argc, argv);
   int x = cli.receiveInteger("-x");
   float y = cli.receiveFloating("--y-axis");
   float r = x * y;

   std::cout << ">>> " << argv[0] << "\n";

   if (cli.receiveSimple("-h")) {
      std::cout << argv[0] << " -x -y \n";
   } else {
      std::cout << cli.receiveText("-t") << '\n';
      std::cout << "Input file: " << cli.receiveInFile("-f") << '\n';
      std::cout << "Output file: " << cli.receiveOutFile("-o") << '\n';
      std::cout << ">>> x: " << x << "\n";
      std::cout << ">>> y: " << y << "\n";
      std::cout << ">>> result: " << r << "\n";

      for (std::string e : cli.receiveBuffer()) {
         std::cout << ">>> Buffer: " << e << "\n";
      }
   }
}