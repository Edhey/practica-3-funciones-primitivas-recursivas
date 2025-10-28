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
 * @file primitive-recursive-function.cc
 * @brief Implementation of base class for primitive recursive functions
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "primitive-recursive-function/primitive-recursive-function.h"

#include <iostream>

#include "validator/validator.h"

/**
 * @brief Applies the primitive recursive function to the given arguments
 * @param args The arguments to apply the function to
 * @return The result of the function application
 */
std::expected<unsigned int, std::string> PrimitiveRecursiveFunction::apply(
    const std::vector<unsigned int>& args) const {
  counter_->Increment();

  if (auto error = Validator::validateArity(args, arity_)) {
    return std::unexpected(*error);
  }

  return function(args);
}