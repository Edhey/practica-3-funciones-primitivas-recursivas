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
 * @file recursive-function-execution.cc
 * @brief Implementation of execution orchestrator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "recursive-function-execution.h"

#include <iostream>

#include "io/input-strategy/console/console-input-strategy.h"
#include "io/input-strategy/file/file-input-strategy.h"
#include "io/output-strategy/console/console-output-strategy.h"
#include "io/output-strategy/file/file-output-strategy.h"
#include "primitive-recursive-function/factory/primitive-function-factory.h"
#include "primitive-recursive-function/validator/validator.h"

RecursiveFunctionExecution::RecursiveFunctionExecution(const ArgsParser& args)
    : args_(args),
      counter_(std::make_shared<Counter>()),
      input_strategy_(nullptr),
      output_strategy_(nullptr),
      function_(nullptr) {}

std::unique_ptr<InputStrategy>
RecursiveFunctionExecution::createInputStrategy() {
  if (!args_.getInputFile().empty()) {
    return std::make_unique<FileInputStrategy>(args_.getInputFile());
  }
  return std::make_unique<ConsoleInputStrategy>();
}

std::expected<std::unique_ptr<OutputStrategy>, std::string>
RecursiveFunctionExecution::createOutputStrategy() {
  if (args_.getOutputFile().empty()) {
    return std::make_unique<ConsoleOutputStrategy>();
  }

  auto file_strategy = FileOutputStrategy::create(args_.getOutputFile());
  if (!file_strategy.has_value()) {
    return std::unexpected(file_strategy.error());
  }

  return std::move(file_strategy.value());
}

std::expected<
    std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>,
    std::string>
RecursiveFunctionExecution::createFunction() {
  try {
    auto func = FunctionFactory::createFunction(args_.getOperation(), counter_);
    return func;
  } catch (const std::invalid_argument& e) {
    return std::unexpected(std::string("Invalid operation: ") + e.what());
  } catch (const std::exception& e) {
    return std::unexpected(std::string("Error creating function: ") + e.what());
  }
}

void RecursiveFunctionExecution::printWelcomeMessage() const {
  std::cout << "Primitive Recursive Function Calculator\n"
            << "Operation: " << args_.getOperation() << "\n"
            << "Enter arguments (2 natural numbers per line)\n"
            << "Press Ctrl+D to end\n"
            << std::endl;
}

std::optional<std::string> RecursiveFunctionExecution::validateArguments(
    const std::vector<unsigned int>& arguments) const {
  // Convert to signed for validation
  std::vector<int> signed_args;
  for (auto arg : arguments) {
    signed_args.push_back(static_cast<int>(arg));
  }

  return Validator::validateNatural(signed_args);
}

std::expected<bool, std::string> RecursiveFunctionExecution::processArguments(
    const std::vector<unsigned int>& arguments) {
  if (auto error = validateArguments(arguments)) {
    return std::unexpected(*error);
  }

  counter_->Reset();

  auto result = function_->apply(arguments);
  if (!result.has_value()) {
    return std::unexpected(result.error());
  }

  if (args_.isVerboseMode()) {
    output_strategy_->writeResult(args_.getOperation(), arguments,
                                  result.value(), counter_->getValue());
  } else {
    output_strategy_->writeResult(args_.getOperation(), arguments,
                                  result.value());
  }

  return true;
}

std::expected<bool, std::string> RecursiveFunctionExecution::run() {
  auto function_result = createFunction();
  if (!function_result.has_value()) {
    return std::unexpected(function_result.error());
  }
  function_ = function_result.value();

  input_strategy_ = createInputStrategy();
  auto output_result = createOutputStrategy();
  if (!output_result.has_value()) {
    return std::unexpected(output_result.error());
  }
  output_strategy_ = std::move(output_result.value());

  if (!args_.getInputFile().empty()) {
    auto* file_strategy =
        dynamic_cast<FileInputStrategy*>(input_strategy_.get());
    if (file_strategy && !file_strategy->isOpen()) {
      return std::unexpected("Failed to open input file: " +
                             args_.getInputFile());
    }
  }

  if (!args_.getArguments().empty()) {
    auto result = processArguments(args_.getArguments());
    if (!result.has_value()) {
      return std::unexpected(result.error());
    }
    return true;
  }

  bool is_interactive = args_.getInputFile().empty();
  if (is_interactive) {
    printWelcomeMessage();
  }

  std::vector<unsigned int> arguments;
  while (input_strategy_->getNextInput(arguments)) {
    auto result = processArguments(arguments);
    if (!result.has_value()) {
      if (is_interactive) {
        std::cerr << "Error: " << result.error() << std::endl;
      } else {
        return std::unexpected(result.error());
      }
    }
  }

  return true;
}
