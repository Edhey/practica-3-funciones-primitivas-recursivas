/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Practice 3: Primitive Recursive Functions
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Oct 27 2025
 * @file ArgsParser.h
 * @brief Command-line argument parser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <optional>
#include <string>
#include <vector>

/**
 * @brief Parses command-line arguments for the ./primitive-recursive-function
 * calculator
 */
class ArgsParser {
public:
  static void printUsage(std::string program_name);
  static std::optional<ArgsParser> parse(int argc, char const* argv[]);

  std::string getOperation() const { return operation_; }
  std::vector<unsigned int> getArguments() const { return arguments_; }
  std::string getOutputFile() const { return output_file_; }
  bool isVerboseMode() const { return verbose_mode_; }
  bool isTraceMode() const { return trace_mode_; }

private:
  ArgsParser(const std::string& operation,
             const std::vector<unsigned int>& arguments,
             const std::string& output_file = "", bool verbose_mode = false,
             bool trace_mode = false)
      : operation_(operation),
        arguments_(arguments),
        output_file_(output_file),
        verbose_mode_(verbose_mode),
        trace_mode_(trace_mode) {}

  std::string operation_;
  std::vector<unsigned int> arguments_;
  std::string output_file_;
  bool verbose_mode_;
  bool trace_mode_;
};

#endif  // ARGS_PARSER_H
