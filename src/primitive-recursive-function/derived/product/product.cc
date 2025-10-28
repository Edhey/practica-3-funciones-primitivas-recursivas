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
 * @file Product.cc
 * @brief Implementation of Product function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "product.h"

#include "../../operators/composition/composition.h"
#include "../../operators/primitive-recursion/primitive-recursion.h"
#include "../../primitives/projection/projection.h"
#include "../../primitives/zero/zero.h"
#include "../sum/sum.h"

Product::Product(std::shared_ptr<Counter> counter)
    : PrimitiveRecursiveFunction(counter, 2) {
  // product(x, 0) = 0
  // Base case: product(x, 0) = g(x) = Zero(x) = 0
  auto base_case = std::make_shared<Zero>(counter);

  // product(x, s(y)) = h(x, y, product(x, y)) =
  //                                = sum([P^3_1 x P^3_3](x, y, product(x, y)))
  auto sum = std::make_shared<Sum>(counter);

  auto p1_result = Projection::create(3, 1, counter);
  if (!p1_result.has_value()) {
    throw std::runtime_error("Failed to create P^3_1 for Product: " +
                             p1_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> p1 = p1_result.value();

  auto p3_result = Projection::create(3, 3, counter);
  if (!p3_result.has_value()) {
    throw std::runtime_error("Failed to create P^3_3 for Product: " +
                             p3_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> p3 = p3_result.value();

  auto recursive_case_result = Composition::create(
      sum, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p1, p3});

  if (!recursive_case_result.has_value()) {
    throw std::runtime_error("Failed to create recursive case for Product: " +
                             recursive_case_result.error());
  }
  auto recursive_case = recursive_case_result.value();

  // Build the PrimitiveRecursion
  auto recursion_result = PrimitiveRecursion::create(base_case, recursive_case);
  if (!recursion_result.has_value()) {
    throw std::runtime_error("Failed to create recursion for Product: " +
                             recursion_result.error());
  }
  implementation_ = recursion_result.value();
}

std::expected<unsigned int, std::string> Product::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
