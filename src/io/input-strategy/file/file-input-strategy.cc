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
 * @file file-input-strategy.cc
 * @brief Implementation of FileInputStrategy
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "io/input-strategy/file/file-input-strategy.h"

#include <iostream>

FileInputStrategy::FileInputStrategy(const std::string& filename)
    : file_(filename) {
  if (!file_.is_open()) {
    std::cerr << "Error: Could not open input file '" << filename << "'\n";
  }
}

FileInputStrategy::~FileInputStrategy() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool FileInputStrategy::getNextInput(std::vector<unsigned int>& args) {
  args.clear();

  if (!file_.is_open()) {
    return false;
  }

  std::string line;
  while (std::getline(file_, line)) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#') {
      continue;
    }

    if (parseLine(line, args)) {
      return true;
    }
  }

  return false;  // EOF or no more valid lines
}

bool FileInputStrategy::parseLine(const std::string& line,
                                  std::vector<unsigned int>& args) {
  std::istringstream iss(line);
  unsigned int value;

  while (iss >> value) {
    args.push_back(value);
  }

  // Check if there was a parsing error (non-numeric input)
  if (!iss.eof() && iss.fail()) {
    std::cerr << "Warning: Skipping invalid line: " << line << "\n";
    args.clear();
    return false;
  }

  return !args.empty();
}
