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
 * @file Projection.cc
 * @brief Implementation of Projection primitive function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "primitive-recursive-function/primitives/projection/projection.h"

std::expected<unsigned int, std::string> Projection::function(
    const std::vector<unsigned int>& args) const {
  if (auto error = Validator::validateProjectionIndex(index_, getArity())) {
    return std::unexpected(*error);
  }
  return args[index_ - 1];
}
