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
 * @file zero.h
 * @brief Zero primitive function z(n) = 0
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef ZERO_H
#define ZERO_H

#include <expected>
#include <memory>

#include "primitive-recursive-function.h"
#include "counter/counter.h"

/**
 * @brief Zero primitive function: z(n) = 0
 *
 * Returns 0 for any input argument.
 */
class Zero : public PrimitiveRecursiveFunction {
public:
  explicit Zero(std::shared_ptr<Counter> counter)
      : PrimitiveRecursiveFunction(counter, 1) {}
  std::string getName() const override { return "Zero"; }

private:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;
};

#endif  // ZERO_H
