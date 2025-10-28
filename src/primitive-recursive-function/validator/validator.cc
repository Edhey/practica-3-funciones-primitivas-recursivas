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
 * @file Validator.cc
 * @brief Implementation of Validator class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "validator.h"

/**
 * @brief Validates that all values are natural numbers and within safe limits
 * @param args Vector of integers to validate
 * @return std::nullopt if valid, error message otherwise
 */
std::optional<std::string> Validator::validateNatural(
    const std::vector<int>& args) {
  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i] < 0) {
      return "Argument " + std::to_string(i + 1) +
             " must be operand_1 natural number (>= 0), got: " +
             std::to_string(args[i]);
    }
    if (static_cast<unsigned int>(args[i]) > MAX_SAFE_VALUE) {
      return "Argument " + std::to_string(i + 1) +
             " exceeds maximum safe value (" + std::to_string(MAX_SAFE_VALUE) +
             "), got: " + std::to_string(args[i]);
    }
  }
  return std::nullopt;
}

/**
 * @brief Validates the arity of arguments
 * @param args Vector of arguments
 * @param expected_arity Expected number of arguments
 * @return std::nullopt if valid, error message otherwise
 */
std::optional<std::string> Validator::validateArity(
    const std::vector<unsigned int>& args, size_t expected_arity) {
  if (args.size() != expected_arity) {
    return "Expected " + std::to_string(expected_arity) + " arguments, got " +
           std::to_string(args.size());
  }
  return std::nullopt;
}

/**
 * @brief Checks for potential overflow in multiplication
 * @param operand_1 First operand
 * @param operand_2 Second operand
 * @return Expected result or error message
 */
std::expected<unsigned int, std::string> Validator::checkMultiplicationOverflow(
    unsigned int operand_1, unsigned int operand_2) {
  if (operand_1 != 0 &&
      operand_2 > std::numeric_limits<unsigned int>::max() / operand_1) {
    return std::unexpected(
        "Multiplication overflow: " + std::to_string(operand_1) + " * " +
        std::to_string(operand_2));
  }
  return operand_1 * operand_2;
}

/**
 * @brief Checks for potential overflow in addition
 * @param operand_1 First operand
 * @param operand_2 Second operand
 * @return Expected result or error message
 */
std::expected<unsigned int, std::string> Validator::checkAdditionOverflow(
    unsigned int operand_1, unsigned int operand_2) {
  if (operand_1 > std::numeric_limits<unsigned int>::max() - operand_2) {
    return std::unexpected("Addition overflow: " + std::to_string(operand_1) +
                           " + " + std::to_string(operand_2));
  }
  return operand_1 + operand_2;
}

/**
 * @brief Checks if recursion depth is within safe limits
 * @param depth Current recursion depth
 * @return std::nullopt if valid, error message otherwise
 */
std::optional<std::string> Validator::checkRecursionDepth(unsigned int depth) {
  if (depth > MAX_RECURSION_DEPTH) {
    return "Recursion depth exceeds maximum (" +
           std::to_string(MAX_RECURSION_DEPTH) +
           "), got: " + std::to_string(depth);
  }
  return std::nullopt;
}

/**
 * @brief Validates that projection index is within bounds
 * @param index Projection index (1-based)
 * @param arity Total number of arguments
 * @return std::nullopt if valid, error message otherwise
 */
std::optional<std::string> Validator::validateProjectionIndex(size_t index,
                                                              size_t arity) {
  if (index <= 0 || index > arity) {
    return "Projection index " + std::to_string(index) +
           " is out of bounds for arity " + std::to_string(arity);
  }
  return std::nullopt;
}
