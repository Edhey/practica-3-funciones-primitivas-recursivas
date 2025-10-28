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
      "Usage: {0} <operation> <arg1> <arg2> [options]\n\n"
      "Operations:\n"
      "  sum, add          Calculate x + y\n"
      "  product, mult     Calculate x * y\n"
      "  power, pow        Calculate x^y\n\n"
      "Arguments:\n"
      "  <arg1> <arg2>     Two natural numbers (>= 0)\n\n"
      "Options:\n"
      "  -o, --output <file>  Write result to file\n"
      "  -v, --verbose        Show function call count\n"
      "  -t, --trace          Show detailed execution trace\n"
      "  -h, --help           Show this help message\n\n"
      "Examples:\n"
      "  {0} sum 5 3\n"
      "  {0} power 2 10 -v\n"
      "  {0} product 7 8 -o result.txt\n"
      "  {0} pow 3 4 --trace --verbose\n",
      program_name);
}

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

  if (argc < 4) {
    std::cerr << "Error: Expected operation and two arguments\n\n";
    printUsage(argv[0]);
    return std::nullopt;
  }

  std::string operation = argv[1];
  std::vector<unsigned int> arguments;

  try {
    for (int i = 2; i <= 3; ++i) {
      std::string arg = argv[i];
      if (!arg.empty() && arg[0] == '-') {
        std::cerr << "Error: Expected natural number (>= 0), got option: "
                  << arg << "\n";
        return std::nullopt;
      }

      long long value = std::stoll(arg);
      if (value < 0) {
        std::cerr << "Error: Arguments must be natural numbers (>= 0)\n";
        return std::nullopt;
      }
      arguments.push_back(static_cast<unsigned int>(value));
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: Invalid number format\n";
    return std::nullopt;
  }

  // Parse optional flags
  std::string output_file;
  bool verbose_mode = false;
  bool trace_mode = false;

  for (int i = 4; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-o" || arg == "--output") {
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
    } else {
      std::cerr << "Error: Unknown option: " << arg << "\n\n";
      printUsage(argv[0]);
      return std::nullopt;
    }
  }

  return ArgsParser(operation, arguments, output_file, verbose_mode,
                    trace_mode);
}
