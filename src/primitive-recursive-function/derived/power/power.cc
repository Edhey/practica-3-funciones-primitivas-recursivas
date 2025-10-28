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
 * @file power.cc
 * @brief Implementation of Power function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "power.h"

#include "primitive-recursive-function/derived/product/product.h"
#include "primitive-recursive-function/operators/composition/composition.h"
#include "primitive-recursive-function/operators/primitive-recursion/primitive-recursion.h"
#include "primitive-recursive-function/primitives/projection/projection.h"
#include "primitive-recursive-function/primitives/successor/successor.h"
#include "primitive-recursive-function/primitives/zero/zero.h"

Power::Power(std::shared_ptr<Counter> counter)
    : PrimitiveRecursiveFunction(counter, 2) {
  // power(x, 0) = 1
  // Base case: power(x, 0) = g(x) = s(Zero(P^1_1(x)))
  auto zero = std::make_shared<Zero>(counter);
  auto successor = std::make_shared<Successor>(counter);

  auto base_case_result = Composition::create(
      successor,
      std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{zero});

  if (!base_case_result.has_value()) {
    throw std::runtime_error("Failed to create base case for Power: " +
                             base_case_result.error());
  }
  auto base_case = base_case_result.value();

  // power(x, s(y)) = h(x, y, power(x, y)) =
  //                                   product[P^3_1 x P^3_3](x, y, power(x, y))
  auto product = std::make_shared<Product>(counter);

  auto p1_result = Projection::create(3, 1, counter);
  if (!p1_result.has_value()) {
    throw std::runtime_error("Failed to create P^3_1 for Power: " +
                             p1_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> p1 = p1_result.value();

  auto p3_result = Projection::create(3, 3, counter);
  if (!p3_result.has_value()) {
    throw std::runtime_error("Failed to create P^3_3 for Power: " +
                             p3_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> p3 = p3_result.value();

  auto recursive_case_result = Composition::create(
      product,
      std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p1, p3});

  if (!recursive_case_result.has_value()) {
    throw std::runtime_error("Failed to create recursive case for Power: " +
                             recursive_case_result.error());
  }
  auto recursive_case = recursive_case_result.value();

  // Build the recursion
  auto recursion_result = PrimitiveRecursion::create(base_case, recursive_case);
  if (!recursion_result.has_value()) {
    throw std::runtime_error("Failed to create recursion for Power: " +
                             recursion_result.error());
  }
  implementation_ = recursion_result.value();
}

std::expected<unsigned int, std::string> Power::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
