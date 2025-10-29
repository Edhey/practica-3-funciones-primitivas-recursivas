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
 * @file main.cc
 * @brief Main file for Primitive Recursive Functions calculator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include <iostream>
#include <memory>

#include "counter/counter.h"
#include "input-strategy/console/console-input-strategy.h"
#include "input-strategy/file/file-input-strategy.h"
#include "input-strategy/input-strategy.h"
#include "output-strategy/console/console-output-strategy.h"
#include "output-strategy/file/file-output-strategy.h"
#include "parser/args-parser.h"
#include "primitive-recursive-function/factory/primitive-function-factory.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Creates the appropriate input strategy based on arguments
 */
std::unique_ptr<InputStrategy> CreateInputStrategy(const ArgsParser& args) {
  if (!args.getInputFile().empty()) {
    return std::make_unique<FileInputStrategy>(args.getInputFile());
  }
  return std::make_unique<ConsoleInputStrategy>();
}

/**
 * @brief Creates the appropriate output strategy based on arguments
 */
std::unique_ptr<OutputStrategy> CreateOutputStrategy(const ArgsParser& args) {
  if (args.getOutputFile().empty()) {
    return std::make_unique<ConsoleOutputStrategy>();
  }
  return std::make_unique<FileOutputStrategy>(args.getOutputFile());
}

/**
 * @brief Processes a single set of arguments with the function
 */
void ProcessArguments(
    const std::vector<unsigned int>& arguments, const std::string& operation,
    std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
        function,
    std::shared_ptr<Counter> counter, OutputStrategy& output_strategy,
    bool verbose_mode) {
  // Validate arguments are natural numbers
  std::vector<int> signed_args;
  for (auto arg : arguments) {
    signed_args.push_back(static_cast<int>(arg));
  }

  if (auto error = Validator::validateNatural(signed_args)) {
    std::cerr << "Error: " << *error << std::endl;
    return;
  }

  // Reset counter before execution
  counter->Reset();

  // Execute the function
  auto result = function->apply(arguments);
  if (!result.has_value()) {
    std::cerr << "Error: " << result.error() << std::endl;
    return;
  }

  // Write result
  if (verbose_mode) {
    output_strategy.writeResult(operation, arguments, result.value(),
                                counter->getValue());
  } else {
    output_strategy.writeResult(operation, arguments, result.value());
  }
}

/**
 * @brief Main execution loop for processing inputs
 */
void RunCalculator(
    std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
        function,
    InputStrategy& input_strategy, OutputStrategy& output_strategy,
    const ArgsParser& args) {
  std::vector<unsigned int> arguments;

  // If arguments were provided in command line, use them
  if (!args.getArguments().empty()) {
    arguments = args.getArguments();
    ProcessArguments(arguments, args.getOperation(), function,
                     std::make_shared<Counter>(), output_strategy,
                     args.isVerboseMode());
    return;
  }

  // Otherwise, read from input strategy (interactive or file)
  bool is_interactive = args.getInputFile().empty();

  if (is_interactive) {
    std::cout << "Primitive Recursive Function Calculator\n"
              << "Operation: " << args.getOperation() << "\n"
              << "Enter arguments (two natural numbers per line)\n"
              << "Press Ctrl+D to end\n"
              << std::endl;
  }

  auto counter = std::make_shared<Counter>();

  while (input_strategy.getNextInput(arguments)) {
    ProcessArguments(arguments, args.getOperation(), function, counter,
                     output_strategy, args.isVerboseMode());
  }
}

int main(int argc, char const* argv[]) {
  try {
    // Parse command-line arguments
    auto args_opt = ArgsParser::parse(argc, argv);
    if (!args_opt.has_value()) {
      return 1;
    }
    ArgsParser args = args_opt.value();

    // Create the requested function
    auto counter = std::make_shared<Counter>();
    auto function =
        FunctionFactory::createFunction(args.getOperation(), counter);

    // Create input and output strategies
    auto input_strategy = CreateInputStrategy(args);
    auto output_strategy = CreateOutputStrategy(args);

    // Check if file input strategy failed to open
    if (!args.getInputFile().empty()) {
      auto* file_strategy =
          dynamic_cast<FileInputStrategy*>(input_strategy.get());
      if (file_strategy && !file_strategy->isOpen()) {
        return 1;
      }
    }

    // Run the calculator
    RunCalculator(function, *input_strategy, *output_strategy, args);

    return 0;

  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
    return 1;
  }
}
