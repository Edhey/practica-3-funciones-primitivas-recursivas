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
 * @file file-output-strategy.cc
 * @brief Implementation of FileOutputStrategy
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include <iostream>

#include "io/output-strategy/file/file-output-strategy.h"

std::expected<std::unique_ptr<FileOutputStrategy>, std::string>
FileOutputStrategy::create(const std::string& filename) {
  auto strategy =
      std::unique_ptr<FileOutputStrategy>(new FileOutputStrategy(filename));

  if (!strategy->file_.is_open()) {
    return std::unexpected("Could not open file: " + filename);
  }

  return strategy;
}

FileOutputStrategy::FileOutputStrategy(const std::string& filename)
    : file_(filename) {}

void FileOutputStrategy::writeResult(const std::string& operation,
                                     const std::vector<unsigned int>& args,
                                     unsigned int result,
                                     unsigned int call_count) {
  std::ostream& out = getStream();

  // Print operation with arguments
  out << operation << "(";
  for (size_t i = 0; i < args.size(); ++i) {
    if (i > 0)
      out << ", ";
    out << args[i];
  }
  out << ") = " << result << "\n";

  // Print call count if provided (verbose mode)
  if (call_count > 0) {
    out << "Function calls: " << call_count << "\n";
  }
}
