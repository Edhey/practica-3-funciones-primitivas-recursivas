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
  auto base_case_result = Projection::create(1, 1, counter);
  if (!base_case_result.has_value()) {
    throw std::runtime_error("Failed to create base case for Sum: " +
                             base_case_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> base_case =
      base_case_result.value();

  // sum(x, s(y)) = h(x, y, sum(x, y)) = s(P^3_3(x, y, sum(x, y)))
  auto successor = std::make_shared<Successor>(counter);

  auto p3_result = Projection::create(3, 3, counter);
  if (!p3_result.has_value()) {
    throw std::runtime_error("Failed to create projection for Sum: " +
                             p3_result.error());
  }
  std::shared_ptr<PrimitiveRecursiveFunction> p3 = p3_result.value();

  auto recursive_case_result = Composition::create(
      successor, std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>{p3});

  if (!recursive_case_result.has_value()) {
    throw std::runtime_error("Failed to create recursive case for Sum: " +
                             recursive_case_result.error());
  }
  auto recursive_case = recursive_case_result.value();

  // Build the PrimitiveRecursion
  auto recursion_result = PrimitiveRecursion::create(base_case, recursive_case);
  if (!recursion_result.has_value()) {
    throw std::runtime_error("Failed to create recursion for Sum: " +
                             recursion_result.error());
  }
  implementation_ = recursion_result.value();
}

std::expected<unsigned int, std::string> Sum::function(
    const std::vector<unsigned int>& args) const {
  return implementation_->apply(args);
}
