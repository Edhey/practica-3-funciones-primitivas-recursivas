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
 * @file input-strategy.h
 * @brief Strategy pattern for reading input arguments
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef INPUT_STRATEGY_H
#define INPUT_STRATEGY_H

#include <string>
#include <vector>

/**
 * @brief Abstract base class for input strategies
 */
class InputStrategy {
public:
  virtual ~InputStrategy() = default;

  /**
   * @brief Gets the next set of input arguments
   * @param args Reference to store the input arguments
   * @return true if input was read successfully, false if no more input
   */
  virtual bool getNextInput(std::vector<unsigned int>& args) = 0;
};

#endif  // INPUT_STRATEGY_H
