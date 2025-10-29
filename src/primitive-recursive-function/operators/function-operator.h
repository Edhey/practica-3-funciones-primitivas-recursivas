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
template <typename ArgsType, typename ReturnType>
class FunctionOperator
    : public PrimitiveRecursiveFunction<ArgsType, ReturnType> {
public:
  virtual ~FunctionOperator() = default;
  FunctionOperator(int arity)
      : PrimitiveRecursiveFunction<ArgsType, ReturnType>(nullptr, arity) {}
  std::expected<ReturnType, std::string> apply(
      const std::vector<ArgsType>& args) const final override;
};

template <typename ArgsType, typename ReturnType>
inline std::expected<ReturnType, std::string>
FunctionOperator<ArgsType, ReturnType>::apply(
    const std::vector<ArgsType>& args) const {
  if (auto error = this->validateArity(args)) {
    return std::unexpected(*error);
  }
  return this->function(args);
}

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_OPERATOR_H