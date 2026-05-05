# IEEE‑754 Double‑Precision Decoder (Mathematical Reconstruction in C)

This project implements the **mathematical reconstruction** of a 64‑bit IEEE‑754 double‑precision floating‑point number from its raw bit fields.  
It assumes you already have a 64‑element array of `unsigned int` bits (0 or 1), and it decodes:

- The **sign bit**
- The **11‑bit exponent**
- The **52‑bit mantissa (fraction)**
- The final floating‑point value using the IEEE‑754 formula

This implementation is educational and demonstrates how a `double` is computed internally without relying on unions, bit‑fields, or compiler‑specific behavior.

---

## IEEE‑754 Double Format (64‑bit)

A double‑precision floating‑point number is structured as:

| Field     | Bits | Description |
|-----------|------|-------------|
| Sign      | 1    | 0 = positive, 1 = negative |
| Exponent  | 11   | Biased by 1023 |
| Mantissa  | 52   | Fractional part |

The value is computed as:

value = sign × (1 + mantissa) × 2^(exponent - 1023)


---

## What This Code Does

### ✔ Extracts the exponent  
`get_exp_value()` converts the 11 exponent bits into an integer and subtracts the IEEE‑754 bias (1023).

### ✔ Computes the mantissa  
`get_mantissa_value()` sums powers of 2⁻ⁿ for each mantissa bit that is set to 1.

### ✔ Determines the sign  
`get_sign()` returns `+1.0` or `-1.0`.

### ✔ Reconstructs the final floating‑point value  
`IEEE_754()` splits the 64‑bit array into exponent and mantissa fields, then calls:

IEEE_754_MATH(exp, mantissa)


which performs the full IEEE‑754 calculation.

---

## Function Breakdown

### `get_decimal_value(i)`
Computes \(2^i\).  
Used for exponent reconstruction.

### `get_exp_value(top_value, bits, bias)`
Converts the exponent bit array into an integer and subtracts the IEEE‑754 bias.

### `get_mantissa_bit_value(i)`
Returns the value of the mantissa bit at position `i`

### `get_mantissa_value(top_value, bits)`
Sums all mantissa bit contributions.

### `get_sign(binary)`
Returns `1.0` or `-1.0` based on the first bit.

### `IEEE_754_MATH(exp, mantissa)`
Computes: (1 + mantissa) × 2^(exponent)

### `IEEE_754(binary)`
Splits the 64‑bit array into:

- 1 sign bit  
- 11 exponent bits  
- 52 mantissa bits  

Then reconstructs the final value.

---

## Example Usage

This version of the code expects a 64‑bit array of bits:

```c
unsigned int binary[64] = { /* 0s and 1s representing a double */ };

double result = IEEE_754(binary);
