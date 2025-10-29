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
 * @file sum.cc
 * @brief Implementation of Sum function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "sum.h"

#include "../../operators/composition/composition.h"
#include "../../operators/primitive-recursion/primitive-recursion.h"
#include "../../primitives/projection/projection.h"
#include "../../primitives/successor/successor.h"

Sum::Sum(std::shared_ptr<Counter> counter)
    : PrimitiveRecursiveFunction(counter, 2) {
  // sum(x, 0) = x
  // Base case: g(x) = P^1_1(x) = x
  auto base_case = std::make_shared<Projection>(1, 1, counter);

  // sum(x, s(y)) = h(x, y, sum(x, y)) = s(P^3_3(x, y, sum(x, y)))
  auto successor = std::make_shared<Successor>(counter);

  auto projection3_3 = std::make_shared<Projection>(3, 3, counter);
  auto recursive_case = std::make_shared<Composition>(
      successor,
      std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{projection3_3});

  // Build the PrimitiveRecursion
  auto recursion =
      std::make_shared<PrimitiveRecursion>(base_case, recursive_case);
  implementation_ = recursion;
}

std::expected<unsigned int, std::string> Sum::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
