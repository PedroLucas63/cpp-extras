#ifndef CLI_HPP_
#define CLI_HPP_

#include "Argument.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Namespace 'ext' for external utilities and extensions.
 */
namespace ext {
class CLI {
 private:
   std::vector<std::unique_ptr<Argument>> m_arguments;
   std::map<Argument *, bool> m_values_simple;
   std::map<Argument *, std::string> m_values_text;
   std::map<Argument *, int> m_values_int;
   std::map<Argument *, float> m_values_float;
   std::map<ArgumentInFile *, std::string> m_values_infile;
   std::map<ArgumentOutFile *, std::string> m_values_outfile;
   std::map<ArgumentList *, std::vector<std::string>> m_values_list;
   std::vector<std::string> m_buffer;

   Argument *checkArgument(std::string const &argument_) const {
      for (auto &arg : m_arguments) {
         if (arg->checkReferences(argument_)) {
            return arg.get();
         }
      }

      return nullptr;
   }

   bool getText(ArgumentText *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         m_values_text[arg_] = next_;
         return true;
      }

      return false;
   }

   bool getInteger(ArgumentInteger *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         int converted{std::stoi(next_)};
         m_values_int[arg_] = converted;
         return true;
      }

      return false;
   }

   bool getFloating(ArgumentFloating *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         float converted{std::stof(next_)};
         m_values_float[arg_] = converted;
         return true;
      }

      return false;
   }

   bool getInFile(ArgumentInFile *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         m_values_infile[arg_] = next_;
         return true;
      }

      return false;
   }

   bool getOutFile(ArgumentOutFile *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         m_values_outfile[arg_] = next_;
         return true;
      }

      return false;
   }

   bool getlist(ArgumentList *arg_, char *next_) {
      if (arg_->validateData(next_)) {
         m_values_list[arg_].push_back(next_);
         return true;
      }

      return false;
   }

   bool getSimple(Argument *arg_) { m_values_simple[arg_] = true; return true; }

 public:
   CLI() {}

   void addArgument(char ref_, std::string c_ref_ = std::string()) {
      m_arguments.push_back(std::make_unique<Argument>(ref_, c_ref_));
      m_values_simple[m_arguments.back().get()] = false;
   }

   void addArgumentText(char ref_, std::string c_ref_ = std::string()) {
      m_arguments.push_back(std::make_unique<ArgumentText>(ref_, c_ref_));
      m_values_text[m_arguments.back().get()] = std::string();
   }

   void addArgumentInteger(char ref_,
                           std::string c_ref_ = std::string()) {
      m_arguments.push_back(std::make_unique<ArgumentInteger>(ref_, c_ref_));
      m_values_int[m_arguments.back().get()] = int();
   }

   void addArgumentFloating(char ref_,
                            std::string c_ref_ = std::string()) {
      m_arguments.push_back(std::make_unique<ArgumentFloating>(ref_, c_ref_));
      m_values_float[m_arguments.back().get()] = float();
   }

   void addArgumentInFile(
       char ref_, std::string c_ref_ = std::string(),
       std::initializer_list<std::string> const &extensions_ = {}) {
      m_arguments.push_back(
          std::make_unique<ArgumentInFile>(ref_, c_ref_, extensions_));
      m_values_infile[static_cast<ArgumentInFile *>(m_arguments.back().get())] =
          std::string();
   }

   void addArgumentOutFile(
       char ref_, std::string c_ref_ = std::string(),
       std::initializer_list<std::string> const &extensions_ = {}) {
      m_arguments.push_back(
          std::make_unique<ArgumentOutFile>(ref_, c_ref_, extensions_));
      m_values_outfile[static_cast<ArgumentOutFile *>(
          m_arguments.back().get())] = std::string();
   }

   void addArgumentListFile(
       char ref_, std::string c_ref_ = std::string(),
       std::initializer_list<std::string> const &options_ = {}) {
      m_arguments.push_back(
          std::make_unique<ArgumentList>(ref_, c_ref_, options_));
      m_values_list[static_cast<ArgumentList *>(m_arguments.back().get())] = {};
   }

   void parse(int argc_, char *argv_[]) {
      for (int index{1}; index < argc_; ++index) {
         Argument *argument{checkArgument(argv_[index])};

         if (argument == nullptr) {
            m_buffer.push_back(argv_[index]);
         } else if (ArgumentText *textArg =
                        dynamic_cast<ArgumentText *>(argument)) {
            if (index + 1 < argc_) {
               if (getText(textArg, argv_[index + 1])) {
                  ++index;
               }
            }
         } else if (ArgumentInteger *intArg =
                        dynamic_cast<ArgumentInteger *>(argument)) {
            if (index + 1 < argc_) {
               if (getInteger(intArg, argv_[index + 1])) {
                  ++index;
               }
            }
         } else if (ArgumentFloating *floatArg =
                        dynamic_cast<ArgumentFloating *>(argument)) {
            if (index + 1 < argc_) {
               if (getFloating(floatArg, argv_[index + 1])) {
                  ++index;
               }
            }
         } else if (ArgumentInFile *inputFileArg =
                        dynamic_cast<ArgumentInFile *>(argument)) {
            if (index + 1 < argc_) {
               if (getInFile(inputFileArg, argv_[index + 1])) {
                  ++index;
               }
            }
         } else if (ArgumentOutFile *outputFileArg =
                        dynamic_cast<ArgumentOutFile *>(argument)) {
            if (index + 1 < argc_) {
               if (getOutFile(outputFileArg, argv_[index + 1])) {
                  ++index;
               }
            }
         } else if (ArgumentList *listArg =
                        dynamic_cast<ArgumentList *>(argument)) {
            while (index + 1 < argc_) {
               if (getlist(listArg, argv_[index + 1])) {
                  ++index;
               } else {
                  break;
               }
            }
         } else {
            getSimple(argument);
         }
      }
   }

   bool receiveSimple(std::string argument_) const {
      for (auto [arg, value] : m_values_simple) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return false;
   }

   std::string receiveText(std::string argument_) const {
      for (auto [arg, value] : m_values_text) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return std::string();
   }

   int receiveInteger(std::string argument_) const {
      for (auto [arg, value] : m_values_int) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return int();
   }

   float receiveFloating(std::string argument_) const {
      for (auto [arg, value] : m_values_float) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return float();
   }

   std::string receiveInFile(std::string argument_) const {
      for (auto [arg, value] : m_values_infile) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return std::string();
   }

   std::string receiveOutFile(std::string argument_) const {
      for (auto [arg, value] : m_values_outfile) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return std::string();
   }

   std::vector<std::string> receiveList(std::string argument_) const {
      for (auto [arg, value] : m_values_list) {
         if (arg->checkReferences(argument_)) {
            return value;
         }
      }

      return {};
   }

   std::vector<std::string> receiveBuffer() const { return m_buffer; }
};
} // namespace ext

#endif /// CLI_HPP_