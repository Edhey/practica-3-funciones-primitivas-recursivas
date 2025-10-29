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
  auto projection3_1 = std::make_shared<Projection>(3, 1, counter);
  auto projection3_3 = std::make_shared<Projection>(3, 3, counter);
  auto recursive_case = std::make_shared<Composition>(
      sum, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{projection3_1, projection3_3});
  auto recursion = std::make_shared<PrimitiveRecursion>(base_case, recursive_case);
  implementation_ = recursion;
}

std::expected<unsigned int, std::string> Product::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
