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
 * @file composition.h
 * @brief Composition combinator: h = f ∘ (g1, g2, ..., gm): N^n -> N
 *                        f: N^m -> N
 *                        gi,i = 1..m
 *                        gi: N^n -> N
 *
 *                        h: N^n -> N
 *       X = (x1, x2, ..., xn) e N^n -> h(X) = f(g1(X), g2(X), ..., gm(X))
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "primitive-recursive-function/operators/function-operator.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Composition combinator: f(x) = h(g1(x), ..., gm(x))
 *
 * Applies inner functions to the arguments, then applies the outer function
 * to the results.
 */
class Composition : public FunctionOperator {
public:
  /**
   * @brief Private constructor - use create() factory method instead
   */
  Composition(std::shared_ptr<PrimitiveRecursiveFunction> outer,
              std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> inner,
              int arity)
      : FunctionOperator(arity),
        outer_(outer),
        inner_(std::move(inner)),
        construction_error_("") {
    if (auto error = validate(outer_, inner_)) {
      construction_error_ = *error;
    }
  }
  std::string getName() const override { return "Composition"; }
  std::string toString() const override {
    std::string result = outer_->toString() + "∘(";
    for (size_t i = 0; i < inner_.size(); ++i) {
      if (i > 0)
        result += ", ";
      result += inner_[i]->toString();
    }
    result += ")";
    return result;
  }

private:
  std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const override;
  static std::optional<std::string> validate(
      const std::shared_ptr<PrimitiveRecursiveFunction>& outer,
      const std::vector<std::shared_ptr<PrimitiveRecursiveFunction>>& inner);

  std::shared_ptr<PrimitiveRecursiveFunction> outer_;
  std::vector<std::shared_ptr<PrimitiveRecursiveFunction>> inner_;
  std::string construction_error_;
};

#endif  // COMPOSITION_H
