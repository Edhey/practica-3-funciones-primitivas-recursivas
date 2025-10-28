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
 * @file file-output-strategy.h
 * @brief File output strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef FILE_OUTPUT_STRATEGY_H
#define FILE_OUTPUT_STRATEGY_H

#include <fstream>
#include <string>

#include "../output-strategy.h"

/**
 * @brief Strategy for writing output to a file
 */
class FileOutputStrategy : public OutputStrategy {
public:
  explicit FileOutputStrategy(const std::string& filename);
  ~FileOutputStrategy() override = default;

  std::ostream& getStream() override { return file_; }

  void writeResult(const std::string& operation,
                   const std::vector<unsigned int>& args, unsigned int result,
                   unsigned int call_count = 0) override;

private:
  std::ofstream file_;
};

#endif  // FILE_OUTPUT_STRATEGY_H
