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

#include <memory>
#include <string>
#include <vector>

#include "src/counter/counter.h"

/**
 * @brief Interface for all primitive recursive functions
 */
class PrimitiveRecursiveFunction {
public:
  virtual ~PrimitiveRecursiveFunction() = default;

  /**
   * @brief Applies the function to the given arguments
   * @param args Vector of natural numbers (arguments)
   * @return Result of applying the function
   */
  virtual unsigned int apply(const std::vector<unsigned int>& args) const;

  /**
   * @brief Gets the name of the function
   * @return Function name as string
   */
  virtual std::string getName() const = 0;

  /**
   * @brief Gets a string representation of the function
   * @return String representation
   */
  virtual std::string toString() const { return getName(); }

private:
  std::shared_ptr<Counter> counter_;
  virtual unsigned int function(
      const std::vector<unsigned int>& args) const = 0;
  int arity_;
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
