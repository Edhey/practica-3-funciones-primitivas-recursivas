/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Practice 3: Primitive Recursive Functions
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Oct 29 2025
 * @file recursive-function-execution.h
 * @brief Orchestrates the execution of primitive recursive functions
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef RECURSIVE_FUNCTION_EXECUTION_H
#define RECURSIVE_FUNCTION_EXECUTION_H

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "counter/counter.h"
#include "input-strategy/input-strategy.h"
#include "output-strategy/output-strategy.h"
#include "parser/args-parser.h"
#include "primitive-recursive-function/primitive-recursive-function.h"

/**
 * @brief Orchestrates the execution loop for primitive recursive functions
 *
 * This class follows the Single Responsibility Principle by focusing solely
 * on coordinating the execution flow: reading inputs, applying functions,
 * and writing outputs.
 */
class RecursiveFunctionExecution {
public:
  /**
   * @brief Constructs the execution orchestrator
   * @param args Parsed command-line arguments
   */
  explicit RecursiveFunctionExecution(const ArgsParser& args);

  /**
   * @brief Executes the main calculation loop
   * @return std::expected with success (true) or error message
   */
  std::expected<bool, std::string> run();

private:
  /**
   * @brief Processes a single set of arguments
   * @param arguments Vector of function arguments
   * @return std::expected with success or error message
   */
  std::expected<bool, std::string> processArguments(
      const std::vector<unsigned int>& arguments);

  /**
   * @brief Creates the appropriate input strategy
   * @return Unique pointer to input strategy
   */
  std::unique_ptr<InputStrategy> createInputStrategy();

  /**
   * @brief Creates the appropriate output strategy
   * @return Expected with output strategy or error message
   */
  std::expected<std::unique_ptr<OutputStrategy>, std::string>
  createOutputStrategy();

  /**
   * @brief Creates the requested primitive recursive function
   * @return Expected with function or error message
   */
  std::expected<
      std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>,
      std::string>
  createFunction();

  /**
   * @brief Prints welcome message for interactive mode
   */
  void printWelcomeMessage() const;

  /**
   * @brief Validates that arguments are natural numbers
   * @param arguments Vector of arguments to validate
   * @return std::nullopt if valid, error message otherwise
   */
  std::optional<std::string> validateArguments(
      const std::vector<unsigned int>& arguments) const;

  const ArgsParser& args_;
  std::shared_ptr<Counter> counter_;
  std::unique_ptr<InputStrategy> input_strategy_;
  std::unique_ptr<OutputStrategy> output_strategy_;
  std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
      function_;
};

#endif  // RECURSIVE_FUNCTION_EXECUTION_H
