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
 * @file product.h
 * @brief Product function implemented using primitive PrimitiveRecursion
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <memory>

#include "counter/counter.h"
#include "primitive-recursive-function/primitive-recursive-function.h"

/**
 * @brief Product function: product(x, y) = x * y
 *
 * Implemented using primitive PrimitiveRecursion:
 * - product(x, 0) = 0  (base case: Zero)
 * - product(x, s(y)) = sum(x, product(x, y))  (recursive case)
 */
class Product : public PrimitiveRecursiveFunction<unsigned int, unsigned int> {
public:
  /**
   * @brief Constructs a Product function
   * @param counter Shared pointer to call counter
   */
  explicit Product(std::shared_ptr<Counter> counter);

  std::string getName() const override { return "Product"; }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
      implementation_;
};

#endif  // PRODUCT_H
