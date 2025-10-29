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
 * @file primitive-recursion.h
 * @brief Primitive PrimitiveRecursion combinator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef PrimitiveRecursion_H
#define PrimitiveRecursion_H

#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "primitive-recursive-function/operators/function-operator.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Primitive PrimitiveRecursion combinator
 *
 * Defines a function f(x, y) recursively:
 * - f(x, 0) = g(x)  (base case)
 * - f(x, s(y)) = h(x, y, f(x, y))  (recursive case)
 *
 * where g has arity n-1 and h has arity n+1.
 */
class PrimitiveRecursion : public FunctionOperator {
public:
  /**
   * @brief Private constructor - use create() factory method instead
   */
  PrimitiveRecursion(std::shared_ptr<PrimitiveRecursiveFunction> base_case,
                     std::shared_ptr<PrimitiveRecursiveFunction> recursive_case,
                     int arity)
      : FunctionOperator(arity),
        base_case_(base_case),
        recursive_case_(std::move(recursive_case)),
        construction_error_("") {
    if (auto error = validate(base_case_, recursive_case_)) {
      construction_error_ = *error;
    }
  }
  std::string getName() const override { return "PrimitiveRecursion"; }
  std::string toString() const override {
    return getName() + "(" + base_case_->toString() + ", " +
           recursive_case_->toString() + ")";
  }

private:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction>& base_case,
      const std::shared_ptr<PrimitiveRecursiveFunction>& recursive_case);

  std::shared_ptr<PrimitiveRecursiveFunction> base_case_;
  std::shared_ptr<PrimitiveRecursiveFunction> recursive_case_;
  std::string construction_error_;
};

#endif  // PrimitiveRecursion_H