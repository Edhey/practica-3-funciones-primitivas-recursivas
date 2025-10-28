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
 * @file counter.h
 * @brief Simple counter
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git
 */

#ifndef CALL_COUNTER_H
#define CALL_COUNTER_H

/**
 * @brief A simple counter class
 */
class Counter {
public:
  Counter() : count_(0) {}

  void Increment() { count_++; }
  unsigned int getValue() const { return count_; }
  void Reset() { count_ = 0; }

private:
  unsigned int count_;
};

#endif  // CALL_COUNTER_H
