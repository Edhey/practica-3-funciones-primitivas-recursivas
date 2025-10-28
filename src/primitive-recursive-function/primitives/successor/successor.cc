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
 * @file successor.cc
 * @brief Implementation of Successor primitive function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "successor.h"

#include "../../validator/validator.h"

std::expected<unsigned int, std::string> Successor::function(
    const std::vector<unsigned int>& args) const {
  unsigned int n = args[0];

  // Check for overflow before adding 1
  auto result = Validator::checkAdditionOverflow(n, 1);
  if (!result.has_value()) {
    return std::unexpected(result.error());
  }

  return result.value();
}
