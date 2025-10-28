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
 * @file PrimitiveRecursion.cc
 * @brief Implementation of PrimitiveRecursion combinator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "primitive-recursion.h"

std::expected<std::shared_ptr<PrimitiveRecursion>, std::string>
PrimitiveRecursion::create(
    std::shared_ptr<PrimitiveRecursiveFunction> base_case,
    std::shared_ptr<PrimitiveRecursiveFunction> recursive_case) {
  // Validate inputs
  if (auto error = validate(base_case, recursive_case)) {
    return std::unexpected(*error);
  }

  // Arity is base_case arity + 1 (for the recursion parameter)
  const int arity = base_case->getArity() + 1;

  // Use private constructor with new and wrap in shared_ptr
  auto recursion = std::shared_ptr<PrimitiveRecursion>(
      new PrimitiveRecursion(base_case, std::move(recursive_case), arity));

  return recursion;
}

std::optional<std::string> PrimitiveRecursion::validate(
    const std::shared_ptr<PrimitiveRecursiveFunction>& base_case,
    const std::shared_ptr<PrimitiveRecursiveFunction>& recursive_case) {
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

std::expected<unsigned int, std::string> PrimitiveRecursion::function(
    const std::vector<unsigned int>& args) const {
  // This should never be called if construction failed
  if (!construction_error_.empty()) {
    return std::unexpected("Cannot execute recursion: " + construction_error_);
  }

  return apply(args);
}

std::expected<unsigned int, std::string> PrimitiveRecursion::apply(
    const std::vector<unsigned int>& args) const {
  if (auto error = Validator::validateArity(args, getArity())) {
    return std::unexpected(*error);
  }

  // Split arguments: args = [x1, ..., xn, y]
  // where x = [x1, ..., xn] and y is the recursion parameter
  unsigned int y = args.back();
  std::vector<unsigned int> x(args.begin(), args.end() - 1);

  // Check recursion depth
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

  // Compute f(x, y-1) recursively
  auto recursive_result = apply(recursive_args);
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
