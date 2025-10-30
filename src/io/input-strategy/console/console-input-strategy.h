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
 * @file console-input-strategy.h
 * @brief Console input strategy for interactive argument reading
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef CONSOLE_INPUT_STRATEGY_H
#define CONSOLE_INPUT_STRATEGY_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "io/input-strategy/input-strategy.h"

/**
 * @brief Strategy for reading arguments from console (stdin)
 */
class ConsoleInputStrategy : public InputStrategy {
public:
  ConsoleInputStrategy() = default;
  ~ConsoleInputStrategy() override = default;

  /**
   * @brief Gets the next set of arguments from console
   * @param args Reference to store the parsed arguments
   * @return true if input was read successfully, false on EOF or error
   */
  bool getNextInput(std::vector<unsigned int>& args) override;

private:
  /**
   * @brief Parses a line into unsigned integers
   * @param line Line to parse
   * @param args Output vector of arguments
   * @return true if parsing was successful, false otherwise
   */
  bool parseLine(const std::string& line, std::vector<unsigned int>& args);
};

#endif  // CONSOLE_INPUT_STRATEGY_H
