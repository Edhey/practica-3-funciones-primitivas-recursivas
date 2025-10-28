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
 * @file FunctionFactory.h
 * @brief Factory for creating primitive recursive functions
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef FUNCTION_FACTORY_H
#define FUNCTION_FACTORY_H

#include <memory>
#include <string>

#include "../../counter/counter.h"
#include "../primitive-recursive-function.h"

/**
 * @brief Factory for creating primitive recursive functions
 *
 * Provides methods to create commonly used functions with proper
 * Counter injection.
 */
class FunctionFactory {
public:
  /**
   * @brief Creates a Sum function
   * @param counter Shared pointer to call counter
   * @return Shared pointer to Sum function
   */
  static std::shared_ptr<PrimitiveRecursiveFunction> createSum(
      std::shared_ptr<Counter> counter);

  /**
   * @brief Creates a Product function
   * @param counter Shared pointer to call counter
   * @return Shared pointer to Product function
   */
  static std::shared_ptr<PrimitiveRecursiveFunction> createProduct(
      std::shared_ptr<Counter> counter);

  /**
   * @brief Creates a Power function
   * @param counter Shared pointer to call counter
   * @return Shared pointer to Power function
   */
  static std::shared_ptr<PrimitiveRecursiveFunction> createPower(
      std::shared_ptr<Counter> counter);

  /**
   * @brief Creates a function by name
   * @param name Function name ("sum", "product", "power")
   * @param counter Shared pointer to call counter
   * @return Shared pointer to the requested function
   * @throws std::invalid_argument if function name is not recognized
   */
  static std::shared_ptr<PrimitiveRecursiveFunction> createFunction(
      const std::string& name, std::shared_ptr<Counter> counter);
};

#endif  // FUNCTION_FACTORY_H
