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
 * @file zero.cc
 * @brief Implementation of Zero primitive function
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "primitive-recursive-function/primitives/zero/zero.h"

/**
 * @brief Implements the zero primitive function
 * @param args Vector of arguments (ignored)
 * @return Always returns 0
 */
std::expected<unsigned int, std::string> Zero::function(
    const std::vector<unsigned int>&) const {
  return 0;
}
