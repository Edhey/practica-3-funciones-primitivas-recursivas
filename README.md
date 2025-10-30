# Primitive Recursive Functions - Practice 3

- **Author:** Himar Edhey Hernández Alonso
- **Subject:** Complejidad Computacional
- **Repository:** [GitHub Link](https://github.com/Edhey/practica-3-funciones-primitivas-recursivas.git)

---

## Introduction

In this project, we implement primitive recursive functions (./primitive-recursive-function) in C++. The program goal is to create the power function using only primitive recursive functions. The implementation follows SOLID principles and provides a modular, extensible architecture that makes it easy to add new primitive recursive functions.

For that the program implements the following primitive recursive functions:

- **Sum**: `sum(x, y) = x + y`
- **Product**: `product(x, y) = x * y`
- **Power**: `power(x, y) = x^y`

---

## Compilation

### Requirements

- C++20 or higher
- CMake 3.10+
- GCC/Clang with C++20 support

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure CMake
cmake ..

# Compile (Debug mode with sanitizers)
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Or for Release mode
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# The executable will be: build/./primitive-recursive-function
```

---

## Usage

```bash
Usage: ./primitive-recursive-function <operation> [<arg1> <arg2> | -i <file>] [options]

Operations:
  sum, add          Calculate x + y
  product, mult     Calculate x * y
  power, pow        Calculate x^y

Input modes:
  Interactive:      ./primitive-recursive-function <operation>
                    (Enter arguments line by line, Ctrl+D to end)
  Command-line:     ./primitive-recursive-function <operation> <arg1> <arg2>
  File:             ./primitive-recursive-function <operation> -i <input_file>

Arguments:
  <arg1> <arg2>     Two natural numbers (>= 0)

Options:
  -i, --input <file>   Read arguments from file (one pair per line)
  -o, --output <file>  Write results to file
  -v, --verbose        Show function call count
  -h, --help           Show this help message

Examples:
  ./primitive-recursive-function sum              # Interactive mode
  ./primitive-recursive-function sum 5 3          # Single calculation
  ./primitive-recursive-function power 2 10 -v    # With call counter
  ./primitive-recursive-function product -i args.txt -o result.txt  # File I/O
  ./primitive-recursive-function pow --verbose

Input file format (one pair per line):
  5 3
  2 10
  7 8
```

### Example Executions

```bash
# Simple sum
$ ././primitive-recursive-function sum 5 3
sum(5, 3) = 8

# Product with verbose output (shows call count)
$ ././primitive-recursive-function product 4 5 -v
product(4, 5) = 20
Function calls: 127

# Power with output to file
$ ././primitive-recursive-function power 2 10 -o result.txt
$ cat result.txt
power(2, 10) = 1024
```

---

## Mathematical Foundation

First, we define the basic primitive functions used to construct more complex functions.

### Basic Primitive Functions

Basic primitive recursive functions are defined as follows:

1. **Zero function**: `z(n) = 0`
   - Always returns 0

2. **Successor function**: `s(n) = n + 1`
   - Returns the next natural number

3. **Projection function**: `P^n_i(x₁, ..., xₙ) = xᵢ`
   - Extracts the i-th argument from n arguments

### Operators

Primitive recursive operators let you build new functions from existing ones. The three fundamental operators used here are Combination, Composition, and Primitive Recursion.

1. **Combination**:
   - Let `f : N^n -> N^m` and `g : N^n -> N^k`.  
   - The combination `h = (f, g) : N^n -> N^{m+k}` is defined by:  
   - For `X = (x1, ..., xn) ∈ N^n`, `h(X) = (f(X), g(X))`.

2. **Composition**:
   - Let `f : N^m -> N` and `g1, ..., gm : N^n -> N`.  
   - The composition `h = f ∘ (g1, ..., gm) : N^n -> N` is defined by:  
   - For `X = (x1, ..., xn) ∈ N^n`, `h(X) = f(g1(X), ..., gm(X))`.

3. **Primitive Recursion**:
   - Defines a function `F : N^n -> N` by recursion on the last argument. Write `X = (x1, ..., x_{n-1})` and `y` the last argument.  
   - Given `g : N^{n-1} -> N` (base) and `h : N^{n+1} -> N` (step), define `F` by:
   - `F(X, 0) = g(X)` (base case)
   - `F(X, s(y)) = h(X, y, F(X, y))` (recursive case)
   - Here `g` has arity `n-1` and `h` has arity `n+1`. This schema is used to build functions like sum, product and power.

### Derived Functions

Using the basic functions primitive functions and the operators, we define the following derived functions:

1. **Sum**: `sum(x, y) = x + y`
Defined recursively as:
   - `sum(x, 0) = P^1_1(x) = x` (base case)
   - `sum(x, s(y)) = h(x, y, sum(x, y)) = s(P^3_3(x, y, sum(x, y)))` (recursive case)

2. **Product**: `product(x, y) = x * y`
Defined recursively as:
   - `product(x, 0) = zero(x)` (base case)
   - `product(x, s(y)) = h(x, y, product(x, y)) = sum([P³₁ x P³₃](x, y, product(x, y)))` (recursive case)

3. **Power**: `power(x, y) = x^y`
Defined recursively as:
   - `power(x, 0) = g(x) = s(Zero())` (base case: constructed as `s(z(x))`)
   - `power(x, s(y)) = h(x, y, power(x, y)) = product(P^3_1(x,y,z), P^3_3(x,y,z))` (recursive case)

---

## Implementation Details

### Architecture Overview

The project follows a modular, SOLID-compliant architecture:

```text
PrimitiveRecursiveFunction (Interface)
│
├── primitive/
│   ├── Zero
│   ├── Successor
│   └── Projection
│
├── operators/
│   ├── Combination
│   ├── Composition
│   └── PrimitiveRecursion
│
└── derived/
    ├── Sum
    ├── Product
    └── Power
```

### Key Components

1. **`PrimitiveRecursiveFunction`**: Base interface for all primitive recursive functions
   - `apply(args)`: Evaluates the function with given arguments
   - `getArity()`: Returns the number of expected arguments
   - `getName()`: Returns the function name for debugging

2. **`Counter`**: Tracks the number of function calls
   - Used for complexity analysis and verbose output
   - Injected into all primitive functions

3. **`Validator`**: Validates inputs and prevents errors
   - Ensures arguments are natural numbers
   - Prevents overflow in arithmetic operations

4. **Basic Primitive Functions**:
   - `Zero`: Returns 0 for any input
   - `Successor`: Increments input by 1
   - `Projection`: Selects a specific argument

5. **Operators**:
   - `Combination`: `f(x) = (g₁(x), g₂(x))`
   - `Composition`: `f(x) = h(g₁(x), ..., gₘ(x))`
   - `PrimitiveRecursion`: Implements primitive PrimitiveRecursion pattern

6. **Derived Functions**:
   - `Sum`: Built from Successor and PrimitiveRecursion
   - `Product`: Built from Sum and PrimitiveRecursion
   - `Power`: Built from Product and PrimitiveRecursion

7. **`FunctionFactory`**: Creates and configures functions
   - Ensures proper Counter injection
   - Provides a clean API for function creation

8. **`ArgsParser`**: Parses command-line arguments
   - Validates input format
   - Supports various operation names
   - Handles optional flags

9. **Output Strategies** (Strategy Pattern):
   - `ConsoleOutputStrategy`: Writes to stdout
   - `FileOutputStrategy`: Writes to file

10. **Input Strategies** (Strategy Pattern):

- `ConsoleInputStrategy`: Reads from stdin
- `FileInputStrategy`: Reads from file

### Implementation Description

In this project I have followed the Google Guide Style for C++ and SOLID principles to ensure a clean, maintainable codebase. So, each class has a single responsibility, and dependencies are injected to promote loose coupling.

For making this posible I have created first an abstract class called `PrimitiveRecursiveFunction` that defines the interface for all primitive recursive functions. This way I could apply the Template Method pattern that is especially useful in this case because all primitive recursive functions share the same method signatures for apply the function but have different implementations. I used templates for defining the input and output types, allowing flexibility for future extensions, not just int implementations. This form create functions for strings or other types in the future would be easier.

This way, I have implemented the basic primitive functions (Zero, Successor, Projection) as concrete classes inheriting from `PrimitiveRecursiveFunction`, filling the template with `unsigned int` types. Each of these classes implements the `function` method according to their mathematical definitions. This is a private method used by the `apply` method that implements the template pattern, ensuring that each time a primitive function is called, the call is counted by the injected `Counter` instance. As explained before, the counter is a class that keeps track of the number of function calls, injected into each primitive function following the Dependency Injection principle. I have also created a `Validator` class that is used by all primitive functions to validate the input arguments, ensuring they are natural numbers and preventing overflow, following the Single Responsibility Principle.

For making the Operations (Combination, Composition, PrimitiveRecursion) I have created another abstract class called `FunctionOperator` that also inherits from `PrimitiveRecursiveFunction`. This class serves as a base for all operator implementations, redefining the `apply` method cause operations don't count as function calls. Anyways the concrete operator classes implement the `function` method according to their mathematical definitions, using other primitive functions as building blocks.

- `Combination` takes functions and outputs a tuple of their results, validating the arities of them.
- `Composition` takes a function and a function vector, so validates the functions arities and applies them accordingly. Using the results as parameters for the first function. It also supports taking a `Combination` instead of a vector of functions.
- `PrimitiveRecursion` implements the primitive recursion schema, taking a base case function and a recursive case function. It applies the base case when the last argument is zero, and for the recursive case, it applies the recursive function with the appropriate parameters.

This aproximation using recursive functions allows to build complex functions from simpler ones, following the mathematical definitions of primitive recursive functions, using this classes as operators.

Finally, I have implemented the derived functions (Sum, Product, Power) as concrete classes inheriting from `PrimitiveRecursiveFunction`. Each of these classes constructs their functionality using the basic primitive functions and the operators defined. It is really easy to create new derived functions, you just need to define the template of types (unsigned int in this case) and build the function using the operators and basic functions.

Besides, I have created a `FunctionFactory` class that encapsulates the creation logic for primitive recursive functions. This factory ensures that each function is created with the appropriate `Counter` instance injected, promoting consistency and reducing boilerplate code.

Furthermore, I have implemented an `ArgsParser` class to handle command-line argument parsing and validation. This class supports various operation names, input modes (interactive, command-line, file), and optional flags (verbose, output file). It ensures that the provided arguments are valid before proceeding with function execution. Also the I/O operations are implemented using the Strategy Pattern, allowing easy extension for new input/output methods in the future, as in last practices. This way the program workflow is managed easily by the `RecursiveFunctionExecution` class, which orchestrates the input reading, function execution, and output writing based on the parsed arguments.

## Complexity Analysis

The verbose mode (`-v` flag) shows the number of primitive function calls, which gives insight into computational complexity:

```bash
$ ././primitive-recursive-function sum -v
5 3
sum(5, 3) = 8
Function calls: 11

$ ././primitive-recursive-function product -v
4 5
product(4, 5) = 20
Function calls: 147

$ ././primitive-recursive-function power -v
2 10
power(2, 10) = 1024
Function calls: 1050674
```

Update: For easy correction verbose mode is always true now.

---

## IA Use

This project was developed with assistance from GitHub Copilot for:

- Writing boilerplate code
- Suggesting function implementations
- Documentation generation
- Code refactoring suggestions

The architecture and design decisions were made independently, following best practices for C++ and computational complexity theory.
