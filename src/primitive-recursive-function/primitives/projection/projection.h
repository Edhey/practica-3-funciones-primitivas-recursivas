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
#include "primitive-recursive-function/primitive-recursive-function.h"
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
   * @brief Factory method to create a Projection with validation
   * @param arity Total number of arguments (n)
   * @param index Index of the argument to project (i), 1-based
   * @param counter Shared pointer to call counter
   * @return Expected containing shared_ptr to Projection or error message
   */
  static std::expected<std::shared_ptr<Projection>, std::string> create(
      size_t arity, size_t index, std::shared_ptr<Counter> counter) {
    if (auto error = Validator::validateProjectionIndex(index, arity)) {
      return std::unexpected(*error);
    }
    return std::shared_ptr<Projection>(new Projection(arity, index, counter));
  }

  std::string getName() const override {
    return "P^" + std::to_string(getArity()) + "_" + std::to_string(index_);
  }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  /**
   * @brief Private constructor - use create() factory method instead
   * @param arity Total number of arguments (n)
   * @param index Index of the argument to project (i), 1-based
   * @param counter Shared pointer to call counter
   */
  Projection(size_t arity, size_t index, std::shared_ptr<Counter> counter)
      : PrimitiveRecursiveFunction(counter, arity), index_(index) {}

  size_t index_;
};

#endif  // PROJECTION_H
