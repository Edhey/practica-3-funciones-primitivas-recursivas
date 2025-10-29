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
 * @file sum.h
 * @brief Sum function implemented using primitive PrimitiveRecursion
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef SUM_H
#define SUM_H

#include <memory>

#include "../../primitive-recursive-function.h"
#include "counter/counter.h"

/**
 * @brief Sum function: sum(x, y) = x + y
 *
 * Implemented using primitive PrimitiveRecursion:
 * - sum(x, 0) = x  (base case: P^1_1)
 * - sum(x, s(y)) = s(sum(x, y))  (recursive case: s ∘ P^3_3)
 */
class Sum : public PrimitiveRecursiveFunction<unsigned int, unsigned int> {
public:
  /**
   * @brief Constructs a Sum function
   * @param counter Shared pointer to call counter
   */
  explicit Sum(std::shared_ptr<Counter> counter);

  std::string getName() const override { return "Sum"; }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>> implementation_;
};

#endif  // SUM_H
