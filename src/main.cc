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

#include "parser/args-parser.h"
#include "primitive-recursive-function/execution/recursive-function-execution.h"

int main(int argc, char const* argv[]) {
  auto args_opt = ArgsParser::parse(argc, argv);
  if (!args_opt.has_value()) {
    return 1;
  }

  RecursiveFunctionExecution execution(args_opt.value());
  auto result = execution.run();

  if (!result.has_value()) {
    std::cerr << "Error: " << result.error() << std::endl;
    return 1;
  }

  return 0;
}
