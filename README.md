# APC_calculator — Arbitrary‑Precision Calculator in C

## Overview  
`APC_calculator` is a command‑line arbitrary‑precision calculator implemented in C. It allows performing basic arithmetic operations — addition, subtraction, multiplication, and division — on integers of any length (limited only by system memory), using doubly linked lists to store digits.  
It supports signed numbers and handles leading zeros properly, thus avoiding overflow issues common with fixed-size integer types.

## Motivation / Why this project  
Built as a data‑structures & algorithms exercise (and for learning low-level memory and list manipulation in C), this project helps demonstrate how arithmetic on “big numbers” can be implemented without relying on built-in large‑integer libraries.  
It’s useful when you need exact results for very large integers beyond standard type limits (e.g. hundreds or thousands of digits).

## Features / What it does  
- Addition of arbitrarily large integers  
- Subtraction of arbitrarily large integers  
- Multiplication of arbitrarily large integers  
- Division of arbitrarily large integers (integer division)  
- Support for signed numbers (positive/negative)  
- Handling of leading zeros — inputs like `000123` will be normalized correctly  
- No limit on number of digits (only limited by memory)  

## Limitations / What it does **not** do (yet)  
- Does **not** support decimals / fractional numbers — only integers  
- No exponentiation, modulo, or other advanced operations currently  
- No support for negative divisor with remainder semantics (or special handling) beyond integer division  
- No built-in arbitrary‑precision libraries — performance will degrade for extremely large inputs  
- No interactive UI — command‑line only  

## Build / Compilation Instructions  

```bash
git clone https://github.com/your‑username/APC_calculator.git
cd APC_calculator
gcc -o apc main.c addition.c subtraction.c multiplication.c division.c createlist.c apc.h
