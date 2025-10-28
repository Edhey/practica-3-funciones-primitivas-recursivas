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
 * @file main.cc
 * @brief Main file for Primitive Recursive Functions calculator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include <iostream>
#include <memory>

#include "counter/counter.h"
#include "output-strategy/console/console-output-strategy.h"
#include "output-strategy/file/file-output-strategy.h"
#include "parser/args-parser.h"
#include "primitive-recursive-function/factory/primitive-function-factory.h"
#include "primitive-recursive-function/validator/validator.h"

/**
 * @brief Creates the appropriate output strategy based on arguments
 */
std::unique_ptr<OutputStrategy> CreateOutputStrategy(const ArgsParser& args) {
  if (args.getOutputFile().empty()) {
    return std::make_unique<ConsoleOutputStrategy>();
  }
  return std::make_unique<FileOutputStrategy>(args.getOutputFile());
}

int main(int argc, char const* argv[]) {
  try {
    // Parse command-line arguments
    auto args_opt = ArgsParser::parse(argc, argv);
    if (!args_opt.has_value()) {
      return 1;
    }
    ArgsParser args = args_opt.value();

    // Create call counter
    auto counter = std::make_shared<Counter>();

    // Create the requested function
    auto function =
        FunctionFactory::createFunction(args.getOperation(), counter);

    // Validate arguments
    auto arguments = args.getArguments();
    std::vector<int> signed_args;
    for (auto arg : arguments) {
      signed_args.push_back(static_cast<int>(arg));
    }

    auto natural_result = Validator::validateNatural(signed_args);
    if (natural_result.has_value()) {
      std::cerr << "Error: " << natural_result.value() << std::endl;
      return 1;
    }

    // Validate arity
    auto arity_result =
        Validator::validateArity(arguments, function->getArity());
    if (arity_result.has_value()) {
      std::cerr << "Error: " << arity_result.value() << std::endl;
      return 1;
    }

    // Reset counter before execution
    counter->Reset();

    // Execute the function
    auto result = function->apply(arguments);
    if (!result.has_value()) {
      std::cerr << "Error: " << result.error() << std::endl;
      return 1;
    }

    // Create output strategy and write result
    auto output_strategy = CreateOutputStrategy(args);

    if (args.isVerboseMode()) {
      output_strategy->writeResult(args.getOperation(), arguments,
                                   result.value(), counter->getValue());
    } else {
      output_strategy->writeResult(args.getOperation(), arguments,
                                   result.value());
    }

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
