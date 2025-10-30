/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Practice 3: Primitive Recursive Functions
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Oct 29 2025
 * @file console-input-strategy.cc
 * @brief Implementation of ConsoleInputStrategy
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "io/input-strategy/console/console-input-strategy.h"

bool ConsoleInputStrategy::getNextInput(std::vector<unsigned int>& args) {
  args.clear();

  std::string line;
  if (!std::getline(std::cin, line)) {
    return false;  // EOF or error
  }

  // Skip empty lines
  if (line.empty()) {
    return getNextInput(args);  // Recursively try next line
  }

  return parseLine(line, args);
}

bool ConsoleInputStrategy::parseLine(const std::string& line,
                                     std::vector<unsigned int>& args) {
  std::istringstream iss(line);
  unsigned int value;

  while (iss >> value) {
    args.push_back(value);
  }

  // Check if there was a parsing error (non-numeric input)
  if (!iss.eof() && iss.fail()) {
    std::cerr << "Error: Invalid input. Please enter natural numbers separated "
                 "by spaces.\n";
    args.clear();
    return false;
  }

  return !args.empty();
}
