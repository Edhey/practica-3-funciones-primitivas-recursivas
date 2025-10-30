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
template <typename ArgsType, typename ReturnType>
class PrimitiveRecursion : public FunctionOperator<ArgsType, ReturnType> {
public:
  PrimitiveRecursion(
      std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
          base_case,
      std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
          recursive_case,
      std::shared_ptr<Counter> counter = nullptr)
      : FunctionOperator<ArgsType, ReturnType>(base_case->getArity() + 1),
        base_case_(base_case),
        recursive_case_(std::move(recursive_case)),
        recursion_counter_(counter),
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
  std::expected<ReturnType, std::string> function(
      const std::vector<ArgsType>& args) const override;
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
          base_case,
      const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
          recursive_case);

  std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> base_case_;
  std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
      recursive_case_;
  std::shared_ptr<Counter> recursion_counter_;
  std::string construction_error_;
};

template <typename ArgsType, typename ReturnType>
inline std::optional<std::string>
PrimitiveRecursion<ArgsType, ReturnType>::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
        base_case,
    const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
        recursive_case) {
  if (!base_case) {
    return "Base case function cannot be null";
  }

  if (!recursive_case) {
    return "Recursive case function cannot be null";
  }

  // Validate arity constraints
  // If base_case has arity n, then:
  // - recursive_case must have arity n+2 (adds y and recursive result)
  // - this function has arity n+1 (adds the recursion parameter)
  if (recursive_case->getArity() != base_case->getArity() + 2) {
    return "Recursive case arity (" +
           std::to_string(recursive_case->getArity()) +
           ") must be base case arity (" +
           std::to_string(base_case->getArity()) + ") + 2";
  }

  return std::nullopt;  // Valid
}

template <typename ArgsType, typename ReturnType>
inline std::expected<ReturnType, std::string>
PrimitiveRecursion<ArgsType, ReturnType>::function(
    const std::vector<ArgsType>& args) const {
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute recursion: " + construction_error_);
  }

  if (auto error = this->validateArity(args)) {
    return std::unexpected(*error);
  }

  // Split arguments: args = [x1, ..., xn, y]
  // where x = [x1, ..., xn] and y is the recursion parameter
  unsigned int y = args.back();
  std::vector<unsigned int> x(args.begin(), args.end() - 1);
  if (auto error = Validator::checkPrimitiveRecursionDepth(y)) {
    return std::unexpected(*error);
  }

  // Base case: f(x, 0) = g(x)
  if (y == 0) {
    auto result = base_case_->apply(x);
    if (!result.has_value()) {
      return std::unexpected("Base case failed: " + result.error());
    }
    return result.value();
  }

  // Recursive case: f(x, s(y)) = h(x, y-1, f(x, y-1))
  // Build arguments for recursive call: [x, y-1]
  std::vector<unsigned int> recursive_args = x;
  recursive_args.push_back(y - 1);

  recursion_counter_->Increment();
  // Compute f(x, y-1) recursively
  auto recursive_result = this->apply(recursive_args);
  if (!recursive_result.has_value()) {
    return std::unexpected("Recursive call failed: " +
                           recursive_result.error());
  }

  // Build arguments for h: [x, y-1, f(x, y-1)]
  std::vector<unsigned int> h_args = x;
  h_args.push_back(y - 1);
  h_args.push_back(recursive_result.value());

  // Return h(x, y-1, f(x, y-1))
  auto h_result = recursive_case_->apply(h_args);
  if (!h_result.has_value()) {
    return std::unexpected("Recursive case function failed: " +
                           h_result.error());
  }
  return h_result.value();
}

#endif  // PrimitiveRecursion_H