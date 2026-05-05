# IEEE‑754 Double‑Precision Decoder in C

This project implements a manual decoder for **IEEE‑754 double‑precision (64‑bit) floating‑point numbers** using pure C.  
Instead of relying on unions or bit‑fields, the program extracts bits manually, reconstructs the sign, exponent, and mantissa, and computes the final floating‑point value mathematically.

The goal is educational: to show how a `double` is represented internally and how its value is computed from raw binary.

---

## Overview

A 64‑bit IEEE‑754 floating‑point number is structured as:

- **1 bit** — Sign  
- **11 bits** — Exponent (biased by 1023)  
- **52 bits** — Fraction (mantissa)

This program:

1. Converts a `double` into a 64‑bit binary array  
2. Extracts the sign bit  
3. Extracts and decodes the exponent  
4. Extracts and reconstructs the mantissa  
5. Computes the final floating‑point value using the IEEE‑754 formula

---

## File Purpose

The provided C file contains:

### ✔ Bit extraction  
`convert_to_binary()` converts any memory region into an array of `0` and `1` bits (MSB first).

### ✔ Exponent decoding  
`get_exp_value()` reconstructs the exponent field and subtracts the IEEE‑754 bias (1023).

### ✔ Mantissa decoding  
`get_mantissa_value()` computes the fractional part by summing powers of 2⁻ⁿ.

### ✔ Sign extraction  
`get_sign()` returns `+1.0` or `-1.0` depending on the sign bit.

### ✔ Final IEEE‑754 reconstruction  
`IEEE_754()` splits the 64‑bit array into:
- 1 sign bit  
- 11 exponent bits  
- 52 mantissa bits  

Then `IEEE_754_MATH()` computes:

value = sign × (1 + mantissa) × 2^(exponent)
