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
 * @file combination.h
 * @brief Combination: h = f x g: N^n -> N^m+n
 *                        f: N^n -> N^m
 *                        g: N^n -> N^k
 *                        h: N^n -> N^m+k
 *        X = (x1, x2, ..., xn) e N^n -> h(X) = (f(X), g(X))
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef COMBINATION_H
#define COMBINATION_H

#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "primitive-recursive-function/operators/function-operator.h"
#include "primitive-recursive-function/primitive-recursive-function.h"
#include "primitive-recursive-function/validator/validator.h"

class Combination : public FunctionOperator {
public:
  /**
   * @brief Factory method to create a Combination with validation
   * @param first First function f
   * @param second Second function g
   * @return Expected containing shared pointer to Combination or error message
   */
  static std::expected<std::shared_ptr<Combination>, std::string> create(
      std::shared_ptr<PrimitiveRecursiveFunction> first,
      std::shared_ptr<PrimitiveRecursiveFunction> second);

  std::string toString() const override {
    return "Combination(" + first_->toString() + " x " + second_->toString() +
           ")";
  }

  std::string getName() const override { return "Combination"; }

protected:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;

private:
  /**
   * @brief Private constructor - use create() factory method instead
   */
  Combination(std::shared_ptr<PrimitiveRecursiveFunction> first,
              std::shared_ptr<PrimitiveRecursiveFunction> second, int arity)
      : FunctionOperator(arity),
        first_(first),
        second_(std::move(second)),
        construction_error_("") {}

  /**
   * @brief Validates combination structure
   * @return std::nullopt if valid, error message otherwise
   */
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction>& first,
      const std::shared_ptr<PrimitiveRecursiveFunction>& second);

  std::shared_ptr<PrimitiveRecursiveFunction> first_;
  std::shared_ptr<PrimitiveRecursiveFunction> second_;
  std::string construction_error_;
};

#endif  // COMBINATION_H