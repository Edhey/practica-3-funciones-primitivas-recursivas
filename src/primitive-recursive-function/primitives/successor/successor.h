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
 * @file successor.h
 * @brief Successor primitive function s(n) = n + 1
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef SUCCESSOR_H
#define SUCCESSOR_H

#include <expected>
#include <memory>

#include "counter/counter.h"
#include "primitive-recursive-function/primitive-recursive-function.h"

/**
 * @brief Successor primitive function: s(n) = n + 1
 *
 * Returns the successor (n + 1) of the input argument.
 */
class Successor
    : public PrimitiveRecursiveFunction<unsigned int, unsigned int> {
public:
  /**
   * @brief Constructs a Successor function
   * @param counter Shared pointer to call counter
   */
  explicit Successor(std::shared_ptr<Counter> counter)
      : PrimitiveRecursiveFunction(counter, 1) {}

  std::string getName() const override { return "Successor"; }

private:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;
};

#endif  // SUCCESSOR_H
