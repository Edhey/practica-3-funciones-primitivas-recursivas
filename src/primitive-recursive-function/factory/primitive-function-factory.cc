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
 * @file primitive-function-factory.cc
 * @brief Implementation of FunctionFactory
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#include "primitive-function-factory.h"

#include "../derived/power/power.h"
#include "../derived/product/product.h"
#include "../derived/sum/sum.h"

std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
FunctionFactory::createSum(std::shared_ptr<Counter> counter) {
  return std::make_shared<Sum>(counter);
}

std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
FunctionFactory::createProduct(std::shared_ptr<Counter> counter) {
  return std::make_shared<Product>(counter);
}

std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
FunctionFactory::createPower(std::shared_ptr<Counter> counter) {
  return std::make_shared<Power>(counter);
}

std::shared_ptr<PrimitiveRecursiveFunction<unsigned int, unsigned int>>
FunctionFactory::createFunction(const std::string& name,
                                std::shared_ptr<Counter> counter) {
  if (name == "sum" || name == "add" || name == "addition") {
    return createSum(counter);
  } else if (name == "product" || name == "mult" || name == "multiply" ||
             name == "multiplication") {
    return createProduct(counter);
  } else if (name == "power" || name == "pow" || name == "exp" ||
             name == "exponentiation") {
    return createPower(counter);
  } else {
    throw std::invalid_argument("Unknown function: " + name);
  }
}
