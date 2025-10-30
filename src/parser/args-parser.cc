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
 * @file ArgsParser.cc
 * @brief Implementation of ArgsParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "args-parser.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

void ArgsParser::printUsage(std::string program_name) {
  std::cout << std::format(
      "Usage: {0} <operation> [<arg1> <arg2> | -i <file>] [options]\n\n"
      "Operations:\n"
      "  sum, add          Calculate x + y\n"
      "  product, mult     Calculate x * y\n"
      "  power, pow        Calculate x^y\n\n"
      "Input modes:\n"
      "  Interactive:      {0} <operation>\n"
      "                    (Enter arguments line by line, Ctrl+D to end)\n"
      "  Command-line:     {0} <operation> <arg1> <arg2>\n"
      "  File:             {0} <operation> -i <input_file>\n\n"
      "Arguments:\n"
      "  <arg1> <arg2>     Two natural numbers (>= 0)\n\n"
      "Options:\n"
      "  -i, --input <file>   Read arguments from file (one pair per line)\n"
      "  -o, --output <file>  Write results to file\n"
      "  -v, --verbose        Show function call count\n"
      "  -h, --help           Show this help message\n\n"
      "Examples:\n"
      "  {0} sum              # Interactive mode\n"
      "  {0} sum 5 3          # Single calculation\n"
      "  {0} power 2 10 -v    # With call counter\n"
      "  {0} product -i args.txt -o result.txt  # File I/O\n"
      "  {0} pow --verbose\n\n"
      "Input file format (one pair per line):\n"
      "  5 3\n"
      "  2 10\n"
      "  7 8\n",
      program_name);
}

/**
 * @brief Parses command-line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @return Optional ArgsParser instance if successful, std::nullopt on error
 */
std::optional<ArgsParser> ArgsParser::parse(int argc, char const* argv[]) {
  if (argc < 2) {
    std::cerr << "Error: Not enough arguments\n\n";
    printUsage(argv[0]);
    return std::nullopt;
  }

  std::string first_arg = argv[1];
  if (first_arg == "-h" || first_arg == "--help") {
    printUsage(argv[0]);
    return std::nullopt;
  }

  std::string operation = argv[1];
  std::vector<unsigned int> arguments;
  std::string input_file;
  std::string output_file;
  bool verbose_mode = false;
  bool trace_mode = false;

  // Parse arguments and flags
  int i = 2;
  while (i < argc) {
    std::string arg = argv[i];

    if (arg == "-i" || arg == "--input") {
      if (i + 1 < argc) {
        input_file = argv[++i];
      } else {
        std::cerr << "Error: -i/--input requires a filename\n";
        return std::nullopt;
      }
    } else if (arg == "-o" || arg == "--output") {
      if (i + 1 < argc) {
        output_file = argv[++i];
      } else {
        std::cerr << "Error: -o/--output requires a filename\n";
        return std::nullopt;
      }
    } else if (arg == "-v" || arg == "--verbose") {
      verbose_mode = true;
    } else if (arg == "-t" || arg == "--trace") {
      trace_mode = true;
    } else if (arg == "-h" || arg == "--help") {
      printUsage(argv[0]);
      return std::nullopt;
    } else if (arg[0] == '-') {
      std::cerr << "Error: Unknown option: " << arg << "\n\n";
      printUsage(argv[0]);
      return std::nullopt;
    } else {
      // This is a positional argument (number)
      try {
        long long value = std::stoll(arg);
        if (value < 0) {
          std::cerr << "Error: Arguments must be natural numbers (>= 0)\n";
          return std::nullopt;
        }
        arguments.push_back(static_cast<unsigned int>(value));
      } catch (const std::exception& e) {
        std::cerr << "Error: Invalid number format: " << arg << "\n";
        return std::nullopt;
      }
    }
    ++i;
  }

  // Validate input mode
  if (!input_file.empty() && !arguments.empty()) {
    std::cerr
        << "Error: Cannot use both command-line arguments and input file\n";
    return std::nullopt;
  }

  if (input_file.empty() && arguments.size() != 0 && arguments.size() != 2) {
    std::cerr
        << "Error: Expected 0 arguments (interactive) or 2 arguments, got "
        << arguments.size() << "\n";
    return std::nullopt;
  }

  return ArgsParser(operation, arguments, input_file, output_file, verbose_mode,
                    trace_mode);
}
