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
 * @file primitive-recursive-function.h
 * @brief Base abstract class for all primitive recursive functions
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef PRIMITIVE_RECURSIVE_FUNCTION_H
#define PRIMITIVE_RECURSIVE_FUNCTION_H

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "counter/counter.h"

/**
 * @brief Interface for all primitive recursive functions
 */
class PrimitiveRecursiveFunction {
public:
  virtual ~PrimitiveRecursiveFunction() = default;

  virtual std::expected<unsigned int, std::string> apply(
      const std::vector<unsigned int>& args) const;

  /**
   * @brief Gets a string representation of the function
   * @return String representation
   */
  virtual std::string toString() const { return getName(); }

  /**
   * @brief Gets the arity (number of arguments) of the function
   * @return Number of arguments expected
   */
  int getArity() const { return arity_; }

  /**
   * @brief Gets the name of the function
   * @return Function name as string
   */
  virtual std::string getName() const = 0;

protected:
  PrimitiveRecursiveFunction(std::shared_ptr<Counter> counter, int arity)
      : counter_(counter), arity_(arity) {}

  /**
   * @brief Implementation of the function logic
   * @param args Vector of arguments
   * @return Expected result or error message
   */
  virtual std::expected<unsigned int, std::string> function(
      const std::vector<unsigned int>& args) const = 0;

private:
  std::shared_ptr<Counter> counter_;
  int arity_;
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
