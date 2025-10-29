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
 * @brief Interface for operator base class for primitive recursive functions
 * this ones don't increment counter
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef PRIMITIVE_RECURSIVE_FUNCTION_OPERATOR_H
#define PRIMITIVE_RECURSIVE_FUNCTION_OPERATOR_H

#include "primitive-recursive-function/primitive-recursive-function.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Interface for all primitive recursive functions
 */
class FunctionOperator : public PrimitiveRecursiveFunction {
public:
  virtual ~FunctionOperator() = default;
  FunctionOperator(int arity) : PrimitiveRecursiveFunction(nullptr, arity) {}
  std::expected<unsigned int, std::string> apply(
      const std::vector<unsigned int>& args) const final override;
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_OPERATOR_H
