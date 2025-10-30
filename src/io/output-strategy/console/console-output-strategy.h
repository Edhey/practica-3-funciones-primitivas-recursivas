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
 * @file console-output-strategy.h
 * @brief Console output strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef CONSOLE_OUTPUT_STRATEGY_H
#define CONSOLE_OUTPUT_STRATEGY_H

#include <iostream>

#include "io/output-strategy/output-strategy.h"

/**
 * @brief Strategy for writing output to console
 */
class ConsoleOutputStrategy : public OutputStrategy {
public:
  ConsoleOutputStrategy() = default;
  ~ConsoleOutputStrategy() override = default;

  std::ostream& getStream() override { return std::cout; }

  void writeResult(const std::string& operation,
                   const std::vector<unsigned int>& args, unsigned int result,
                   unsigned int call_count = 0) override;
};

#endif  // CONSOLE_OUTPUT_STRATEGY_H
