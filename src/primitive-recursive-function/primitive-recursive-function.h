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
#include <optional>
#include <string>
#include <vector>

#include "counter/counter.h"

/**
 * @brief Interface for all primitive recursive functions
 */
template <typename ArgsType, typename ReturnType>
class PrimitiveRecursiveFunction {
public:
  virtual ~PrimitiveRecursiveFunction() = default;

  virtual std::expected<ReturnType, std::string> apply(
      const std::vector<ArgsType>& args) const;

  /**
   * @brief Gets a string representation of the function
   * @return String representation
   */
  virtual std::string toString() const { return getName(); }

  /**
   * @brief Gets the name of the function
   * @return Function name as string
   */
  virtual std::string getName() const = 0;

  /**
   * @brief Gets the arity (number of arguments) of the function
   * @return Number of arguments expected
   */
  int getArity() const { return arity_; }

protected:
  PrimitiveRecursiveFunction(std::shared_ptr<Counter> counter, int arity)
      : counter_(counter), arity_(arity) {}

  std::optional<std::string> validateArity(
      const std::vector<ArgsType>& args) const;
  /**
   * @brief Implementation of the function logic
   * @param args Vector of arguments
   * @return Expected result or error message
   */
  virtual std::expected<ReturnType, std::string> function(
      const std::vector<ArgsType>& args) const = 0;

private:
  std::shared_ptr<Counter> counter_;
  int arity_;
};

/**
 * @brief Validates the arity of arguments
 * @param args Vector of arguments
 * @return std::nullopt if valid, error message otherwise
 */
template <typename ArgsType, typename ReturnType>
inline std::optional<std::string>
PrimitiveRecursiveFunction<ArgsType, ReturnType>::validateArity(
    const std::vector<ArgsType>& args) const {
  if (static_cast<int>(args.size()) != arity_) {
    return "Expected " + std::to_string(arity_) + " arguments, got " +
           std::to_string(args.size());
  }
  return std::nullopt;
}

/**
 * @brief Applies the function to the given arguments
 * @tparam ArgsType argument type
 * @tparam ReturnType return type
 * @param args vector of arguments
 * @return expected result or error message
 */
template <typename ArgsType, typename ReturnType>
inline std::expected<ReturnType, std::string>
PrimitiveRecursiveFunction<ArgsType, ReturnType>::apply(
    const std::vector<ArgsType>& args) const {
  if (counter_) {
    counter_->Increment();
  }

  if (auto error = this->validateArity(args)) {
    return std::unexpected(*error);
  }

  return function(args);
}

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H