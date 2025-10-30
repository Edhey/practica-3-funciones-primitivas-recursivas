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

#include "primitive-recursive-function/derived/sum/sum.h"
#include "primitive-recursive-function/operators/combination/combination.h"
#include "primitive-recursive-function/operators/composition/composition.h"
#include "primitive-recursive-function/operators/primitive-recursion/primitive-recursion.h"
#include "primitive-recursive-function/primitives/projection/projection.h"
#include "primitive-recursive-function/primitives/zero/zero.h"

Product::Product(std::shared_ptr<Counter> counter)
    : PrimitiveRecursiveFunction(counter, 2), implementation_(nullptr) {
  // product(x, 0) = 0
  // Base case: g(x) = Zero()
  auto base_case = std::make_shared<Zero>(counter);

  // product(x, s(y)) = h(x, y, product(x, y))
  //                                     = sum([P³₁ x P³₃](x, y, product(x, y)))
  auto sum = std::make_shared<Sum>(counter);
  auto projection3_1 = std::make_shared<Projection>(3, 1, counter);
  auto projection3_3 = std::make_shared<Projection>(3, 3, counter);
  auto combination = std::make_shared<Combination<unsigned int, unsigned int>>(
      projection3_1, projection3_3);
  auto recursive_case =
      std::make_shared<Composition<unsigned int, unsigned int>>(sum,
                                                                combination);
  auto recursion =
      std::make_shared<PrimitiveRecursion<unsigned int, unsigned int>>(
          base_case, recursive_case, counter);

  implementation_ = recursion;
}

std::expected<unsigned int, std::string> Product::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
