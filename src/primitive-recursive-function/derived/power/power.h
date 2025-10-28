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
 * @file power.h
 * @brief Power function implemented using primitive PrimitiveRecursion
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef POWER_H
#define POWER_H

#include <memory>

#include "counter/counter.h"
#include "primitive-recursive-function/primitive-recursive-function.h"

/**
 * @brief Power function: power(x, y) = x^y
 *
 * Implemented using primitive PrimitiveRecursion:
 * - power(x, 0) = 1  (base case)
 * - power(x, s(y)) = product(x, power(x, y))  (recursive case)
 */
class Power : public PrimitiveRecursiveFunction {
public:
  /**
   * @brief Constructs a Power function
   * @param counter Shared pointer to call counter
   */
  explicit Power(std::shared_ptr<Counter> counter);

  std::string getName() const override { return "Power"; }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  std::shared_ptr<PrimitiveRecursiveFunction> implementation_;
};

#endif  // POWER_H
