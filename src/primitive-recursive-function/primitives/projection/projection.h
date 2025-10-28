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
 * @file projection.h
 * @brief Projection primitive function P^n_i(x1, ..., xn) = xi
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef PROJECTION_H
#define PROJECTION_H

#include <expected>
#include <memory>

#include "counter/counter.h"
#include "primitive-recursive-function.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Projection primitive function: P^n_i(x1, ..., xn) = xi
 *
 * Returns the i-th argument from the input vector.
 * Index is 1-based (P^3_1 returns the first argument).
 */
class Projection : public PrimitiveRecursiveFunction {
public:
  /**
   * @brief Constructs a Projection function
   * @param arity Total number of arguments (n)
   * @param index Index of the argument to project (i), 1-based
   * @param counter Shared pointer to call counter
   */
  static std::expected<std::unique_ptr<Projection>, std::string> create(
      size_t arity, size_t index, std::shared_ptr<Counter> counter) {
    if (auto error = Validator::validateProjectionIndex(index, arity)) {
      return std::unexpected(*error);
    }
    return std::make_unique<Projection>(arity, index, counter);
  }

  std::string getName() const override {
    return "P^" + std::to_string(arity_) + "_" + std::to_string(index_);
  }

private:
  size_t index_;
  std::string construction_error_;

  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;
};

#endif  // PROJECTION_H
