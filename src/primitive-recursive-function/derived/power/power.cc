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
  auto base_case = std::make_shared<Composition<unsigned int, unsigned int>>(
      successor,
      std::vector<std::shared_ptr<
          PrimitiveRecursiveFunction<unsigned int, unsigned int>>>{zero});

  // Recursive case: power(x, s(y)) = h(x, y, power(x, y)) =
  //                                = product[P^3_1 x P^3_3](x, y, power(x, y))
  auto product = std::make_shared<Product>(counter);
  auto projection3_1 = std::make_shared<Projection>(3, 1, counter);
  auto projection3_3 = std::make_shared<Projection>(3, 3, counter);
  auto recursive_case =
      std::make_shared<Composition<unsigned int, unsigned int>>(
          product, std::vector<std::shared_ptr<
                       PrimitiveRecursiveFunction<unsigned int, unsigned int>>>{
                       projection3_1, projection3_3});
  auto recursion =
      std::make_shared<PrimitiveRecursion<unsigned int, unsigned int>>(
          base_case, recursive_case);
  implementation_ = recursion;
}

std::expected<unsigned int, std::string> Power::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
