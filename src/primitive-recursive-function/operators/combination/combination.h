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
 * @file combination.h
 * @brief Combination: h = f x g: N^n -> N^m+n
 *                        f: N^n -> N^m
 *                        g: N^n -> N^k
 *                        h: N^n -> N^m+k
 *        X = (x1, x2, ..., xn) e N^n -> h(X) = (f(X), g(X))
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef COMBINATION_H
#define COMBINATION_H

#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "primitive-recursive-function/operators/function-operator.h"
#include "primitive-recursive-function/primitive-recursive-function.h"
#include "primitive-recursive-function/validator/validator.h"

template <typename ArgsType, typename ReturnType>
class Combination : public FunctionOperator<ArgsType, std::vector<ReturnType>> {
public:
  Combination(
      std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> first,
      std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> second)
      : FunctionOperator<ArgsType, std::vector<ReturnType>>(first->getArity()),
        first_(first),
        second_(std::move(second)),
        construction_error_("") {
    if (auto error = validate(first_, second_)) {
      construction_error_ = *error;
    }
  }

  std::string toString() const override {
    return "Combination(" + first_->toString() + " x " + second_->toString() +
           ")";
  }

  std::string getName() const override { return "Combination"; }

protected:
  std::expected<std::vector<ReturnType>, std::string> function(
      const std::vector<ArgsType>& args) const override;

private:
  /**
   * @brief Validates combination structure
   * @return std::nullopt if valid, error message otherwise
   */
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
          first,
      const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
          second);

  std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> first_;
  std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> second_;
  std::string construction_error_;
};

template <typename ArgsType, typename ReturnType>
inline std::expected<std::vector<ReturnType>, std::string>
Combination<ArgsType, ReturnType>::function(
    const std::vector<ArgsType>& args) const {
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute combination: " +
                           construction_error_);
  }
  if (auto error = this->validateArity(args)) {
    return std::unexpected(*error);
  }

  // Apply both functions to the arguments
  auto first_result = first_->apply(args);
  if (!first_result.has_value()) {
    return std::unexpected("First function failed: " + first_result.error());
  }

  auto second_result = second_->apply(args);
  if (!second_result.has_value()) {
    return std::unexpected("Second function failed: " + second_result.error());
  }

  return std::vector<ReturnType>{first_result.value(), second_result.value()};
}

template <typename ArgsType, typename ReturnType>
inline std::optional<std::string> Combination<ArgsType, ReturnType>::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
        first,
    const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>
        second) {
  if (!first) {
    return "First function cannot be null";
  }

  if (!second) {
    return "Second function cannot be null";
  }

  // Both functions must have the same arity
  if (first->getArity() != second->getArity()) {
    return "Combination requires both functions to have the same arity. First "
           "has arity " +
           std::to_string(first->getArity()) + " but second has arity " +
           std::to_string(second->getArity());
  }

  return std::nullopt;  // Valid
}

#endif  // COMBINATION_H