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
 * @file output-strategy.h
 * @brief Output strategy interface
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef OUTPUT_STRATEGY_H
#define OUTPUT_STRATEGY_H

#include <ostream>
#include <string>
#include <vector>

/**
 * @brief Interface for output strategies
 */
class OutputStrategy {
public:
  virtual ~OutputStrategy() = default;

  /**
   * @brief Gets the output stream
   * @return Reference to output stream
   */
  virtual std::ostream& getStream() = 0;

  /**
   * @brief Writes the result of a function application
   * @param operation Name of the operation
   * @param args Arguments passed to the function
   * @param result Result of the computation
   * @param call_count Number of function calls (optional)
   */
  virtual void writeResult(const std::string& operation,
                           const std::vector<unsigned int>& args,
                           unsigned int result,
                           unsigned int call_count = 0) = 0;
};

#endif  // OUTPUT_STRATEGY_H
