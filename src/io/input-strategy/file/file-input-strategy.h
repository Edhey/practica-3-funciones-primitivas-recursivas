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
 * @file file-input-strategy.h
 * @brief File input strategy for reading arguments from file
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef FILE_INPUT_STRATEGY_H
#define FILE_INPUT_STRATEGY_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "io/input-strategy/input-strategy.h"

/**
 * @brief Strategy for reading arguments from a file
 */
class FileInputStrategy : public InputStrategy {
public:
  /**
   * @brief Constructs a FileInputStrategy
   * @param filename Path to the input file
   */
  explicit FileInputStrategy(const std::string& filename);
  ~FileInputStrategy() override;

  /**
   * @brief Gets the next set of arguments from file
   * @param args Reference to store the parsed arguments
   * @return true if input was read successfully, false on EOF or error
   */
  bool getNextInput(std::vector<unsigned int>& args) override;

  /**
   * @brief Checks if the file is open and ready
   * @return true if file is open, false otherwise
   */
  bool isOpen() const { return file_.is_open(); }

private:
  std::ifstream file_;

  /**
   * @brief Parses a line into unsigned integers
   * @param line Line to parse
   * @param args Output vector of arguments
   * @return true if parsing was successful, false otherwise
   */
  bool parseLine(const std::string& line, std::vector<unsigned int>& args);
};

#endif  // FILE_INPUT_STRATEGY_H
