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
 * @file composition.cc
 * @brief Implementation of Composition combinator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "composition.h"

std::expected<std::shared_ptr<Composition>, std::string> Composition::create(
    std::shared_ptr<PrimitiveRecursiveFunction> outer,
    std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> inner) {
  // Validate inputs
  if (auto error = validate(outer, inner)) {
    return std::unexpected(*error);
  }

  // All inner functions have the same arity (validated)
  const int arity = inner[0]->getArity();

  // Use private constructor directly with new and wrap in shared_ptr
  auto composition = std::shared_ptr<Composition>(
      new Composition(outer, std::move(inner), arity));

  return composition;
}

std::optional<std::string> Composition::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction>& outer,
    const std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>& inner) {
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

std::expected<unsigned int, std::string> Composition::function(
    const std::vector<unsigned int>& args) const {
  // This should never be called if construction failed
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute composition: " +
                           construction_error_);
  }

  return apply(args);
}

std::expected<unsigned int, std::string> Composition::apply(
    const std::vector<unsigned int>& args) const {
  if (auto error = Validator::validateArity(args, getArity())) {
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
