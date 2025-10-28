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
 * @file primitive-recursive-function.h
 * @brief Implementation of operator base class for primitive recursive
 * functions
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "function-operator.h"

std::expected<unsigned int, std::string> FunctionOperator::apply(
    const std::vector<unsigned int>& args) const {
  if (auto error = Validator::validateArity(args, getArity())) {
    return std::unexpected(*error);
  }
  return function(args);
}