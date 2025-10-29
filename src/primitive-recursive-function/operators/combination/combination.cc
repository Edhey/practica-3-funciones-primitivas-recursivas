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
 * @file combination.cc
 * @brief Combination: h = f x g: N^n -> N^m+n
 *                        f: N^n -> N^m
 *                        g: N^n -> N^k
 *                        h: N^n -> N^m+k
 *        X = (x1, x2, ..., xn) e N^n -> h(X) = (f(X), g(X))
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "combination.h"

std::optional<std::string> Combination::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction>& first,
    const std::shared_ptr<PrimitiveRecursiveFunction>& second) {
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

std::expected<unsigned int, std::string> Combination::function(
    const std::vector<unsigned int>& args) const {
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute combination: " +
                           construction_error_);
  }
  if (auto error = Validator::validateArity(args, getArity())) {
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

  // Combine results using Cantor pairing function: (a+b)(a+b+1)/2 + b
  // Check for overflow in the calculation
  unsigned int a = first_result.value();
  unsigned int b = second_result.value();

  // Check addition overflow: a + b
  auto sum_result = Validator::checkAdditionOverflow(a, b);
  if (!sum_result.has_value()) {
    return std::unexpected(sum_result.error());
  }
  unsigned int sum = sum_result.value();

  // Check addition overflow: (a+b) + 1
  auto sum_plus_one = Validator::checkAdditionOverflow(sum, 1);
  if (!sum_plus_one.has_value()) {
    return std::unexpected(sum_plus_one.error());
  }

  // Check multiplication overflow: (a+b) * (a+b+1)
  auto mult_result =
      Validator::checkMultiplicationOverflow(sum, sum_plus_one.value());
  if (!mult_result.has_value()) {
    return std::unexpected(mult_result.error());
  }

  // Divide by 2
  unsigned int half = mult_result.value() / 2;

  // Check final addition overflow: half + b
  auto final_result = Validator::checkAdditionOverflow(half, b);
  if (!final_result.has_value()) {
    return std::unexpected(final_result.error());
  }

  return final_result.value();
}