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
 * @file validator.h
 * @brief Input validation and error checking
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <expected>
#include <limits>
#include <optional>
#include <string>
#include <vector>

/**
 * @brief Validates inputs and checks for errors in primitive recursive
 * functions
 */
class Validator {
public:
  static constexpr unsigned int MAX_SAFE_VALUE = 1000000;
  static constexpr unsigned int MAX_PrimitiveRecursion_DEPTH = 10000;

  static std::optional<std::string> validateNatural(
      const std::vector<int>& args);
  static std::expected<unsigned int, std::string> checkMultiplicationOverflow(
      unsigned int a, unsigned int b);
  static std::expected<unsigned int, std::string> checkAdditionOverflow(
      unsigned int a, unsigned int b);
  static std::optional<std::string> validateProjectionIndex(size_t index,
                                                            size_t arity);
};

#endif  // VALIDATOR_H
