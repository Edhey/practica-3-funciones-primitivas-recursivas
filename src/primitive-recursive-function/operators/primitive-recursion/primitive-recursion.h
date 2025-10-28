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
   * @brief Factory method to create a PrimitiveRecursion with validation
   * @param base_case Function g for base case
   * @param recursive_case Function h for recursive case
   * @return Expected containing shared pointer to PrimitiveRecursion or error
   * message
   */
  static std::expected<std::shared_ptr<PrimitiveRecursion>, std::string> create(
      std::shared_ptr<PrimitiveRecursiveFunction> base_case,
      std::shared_ptr<PrimitiveRecursiveFunction> recursive_case);

  std::expected<unsigned int, std::string> apply(
      const std::vector<unsigned int>& args) const override;

  std::string getName() const override { return "PrimitiveRecursion"; }

  std::string toString() const override {
    return getName() + "(" + base_case_->getName() + ", " +
           recursive_case_->getName() + ")";
  }

  /**
   * @brief Check if the recursion was constructed successfully
   */
  bool isValid() const { return construction_error_.empty(); }

  /**
   * @brief Get construction error message if any
   */
  std::string getConstructionError() const { return construction_error_; }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  /**
   * @brief Private constructor - use create() factory method instead
   */
  PrimitiveRecursion(std::shared_ptr<PrimitiveRecursiveFunction> base_case,
                     std::shared_ptr<PrimitiveRecursiveFunction> recursive_case,
                     int arity)
      : FunctionOperator(arity),
        base_case_(base_case),
        recursive_case_(std::move(recursive_case)),
        construction_error_("") {}

  /**
   * @brief Validates recursion structure
   * @return std::nullopt if valid, error message otherwise
   */
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction>& base_case,
      const std::shared_ptr<PrimitiveRecursiveFunction>& recursive_case);

  std::shared_ptr<PrimitiveRecursiveFunction> base_case_;
  std::shared_ptr<PrimitiveRecursiveFunction> recursive_case_;
  std::string construction_error_;
};

#endif  // PrimitiveRecursion_H