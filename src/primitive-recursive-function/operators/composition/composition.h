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
 * @file composition.h
 * @brief Composition combinator: h = f ∘ (g1, g2, ..., gm): N^n -> N
 *                        f: N^m -> N
 *                        gi,i = 1..m
 *                        gi: N^n -> N
 *
 *                        h: N^n -> N
 *       X = (x1, x2, ..., xn) e N^n -> h(X) = f(g1(X), g2(X), ..., gm(X))
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "primitive-recursive-function/operators/function-operator.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Composition combinator: f(x) = h(g1(x), ..., gm(x))
 *
 * Applies inner functions to the arguments, then applies the outer function
 * to the results.
 */
template <typename ArgsType, typename ReturnType>
class Composition : public FunctionOperator<ArgsType, ReturnType> {
public:
  Composition(
      std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> outer,
      std::vector<
          std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>>
          inner)
      : FunctionOperator<ArgsType, ReturnType>(inner[0]->getArity()),
        outer_(outer),
        inner_(std::move(inner)),
        construction_error_("") {
    if (auto error = validate(outer_, inner_)) {
      construction_error_ = *error;
    }
  }
  std::string getName() const override { return "Composition"; }
  std::string toString() const override {
    std::string result = outer_->toString() + "∘(";
    for (size_t i = 0; i < inner_.size(); ++i) {
      if (i > 0)
        result += ", ";
      result += inner_[i]->toString();
    }
    result += ")";
    return result;
  }

private:
  std::expected<ReturnType, std::string> function(
      const std::vector<ArgsType>& args) const override;
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
          outer,
      const std::vector<
          std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>>&
          inner);

  std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>> outer_;
  std::vector<std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>>
      inner_;
  std::string construction_error_;
};

template <typename ArgsType, typename ReturnType>
inline std::expected<ReturnType, std::string>
Composition<ArgsType, ReturnType>::function(
    const std::vector<ArgsType>& args) const {
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute composition: " +
                           construction_error_);
  }
  if (auto error = this->validateArity(args)) {
    return std::unexpected(*error);
  }

  // Evaluate all inner functions
  std::vector<unsigned int> inner_results;
  inner_results.reserve(inner_.size());

  for (const auto& func : inner_) {
    auto result = func->apply(args);
    if (!result.has_value()) {
      return std::unexpected("Inner function " + func->getName() +
                             " failed: " + result.error());
    }
    inner_results.push_back(result.value());
  }

  // Apply outer function to results
  auto outer_result = outer_->apply(inner_results);
  if (!outer_result.has_value()) {
    return std::unexpected("Outer function " + outer_->getName() +
                           " failed: " + outer_result.error());
  }

  return outer_result.value();
}

template <typename ArgsType, typename ReturnType>
inline std::optional<std::string> Composition<ArgsType, ReturnType>::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>&
        outer,
    const std::vector<
        std::shared_ptr<PrimitiveRecursiveFunction<ArgsType, ReturnType>>>&
        inner) {
  if (!outer) {
    return "Outer function cannot be null";
  }

  if (inner.empty()) {
    return "Composition requires at least one inner function";
  }

  // Check for null inner functions
  for (size_t i = 0; i < inner.size(); ++i) {
    if (!inner[i]) {
      return "Inner function at index " + std::to_string(i) + " is null";
    }
  }

  // All inner functions must have the same arity
  const int kInnerArity = inner[0]->getArity();
  for (size_t i = 1; i < inner.size(); ++i) {
    if (inner[i]->getArity() != kInnerArity) {
      return "All inner functions must have the same arity. Function at "
             "index " +
             std::to_string(i) + " has arity " +
             std::to_string(inner[i]->getArity()) + " but expected " +
             std::to_string(kInnerArity);
    }
  }

  // Outer function arity must match number of inner functions
  if (outer->getArity() != static_cast<int>(inner.size())) {
    return "Outer function arity (" + std::to_string(outer->getArity()) +
           ") must match number of inner functions (" +
           std::to_string(inner.size()) + ")";
  }

  return std::nullopt;  // Valid
}

#endif  // COMPOSITION_H