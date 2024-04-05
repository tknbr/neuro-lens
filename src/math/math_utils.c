
#define PI 3.14159265358979323846

#define FACTORIAL_2 2
#define FACTORIAL_3 6
#define FACTORIAL_4 24
#define FACTORIAL_5 120
#define FACTORIAL_6 720
#define FACTORIAL_7 5040

/**
 * Computes the floating-point remainder of the division of two numbers.
 * 
 * This function calculates the remainder of x divided by y, similar to the modulus operation for integers.
 * The result has the same sign as the dividend x and is less than y in magnitude.
 *
 * @param x The dividend in the division operation.
 * @param y The divisor in the division operation.
 * @return The remainder of x divided by y. If y is 0.0, the function returns 0.0, indicating an error in division by zero.
 * 
 * Note: The behavior for division by zero is simplified in this implementation. Depending on application requirements,
 *       more sophisticated error handling may be necessary.
 */
static double fmod(double x, double y)
{
    if (y == 0.0) {
        return 0.0; // Division by zero
    }

    double remainder = x - (y * (long long)(x / y));
    if (remainder * y < 0) {
        remainder += y;
    }
    return remainder;
}


/**
 * Calculates the power of a number using exponentiation by squaring.
 * 
 * This function raises x to the power of n efficiently, using an iterative method. It is optimized for 
 * non-negative integer exponents. The algorithm reduces the number of multiplications compared to the 
 * naive approach, especially for large exponents.
 *
 * @param x The base number to be raised to a power.
 * @param n The exponent to which the base number is raised. Although this implementation primarily handles
 *          non-negative integers, a simple modification is demonstrated for handling negative exponents.
 * @return The result of raising x to the power of n. Returns 1 for n = 0 by definition. For negative 
 *         exponents, it returns the reciprocal of the positive exponent result, assuming n is non-negative.
 * 
 * Note: This function assumes non-negative exponents. If negative exponents are provided, it calculates the 
 *       reciprocal of the positive exponent result, which may not be ideal for all use cases. Further
 *       enhancements may be required for comprehensive error handling and to support floating-point exponents.
 */
static double power(double x, int n) {
    if (n == 0) return 1;  // Any number to the power of 0 is 1
    if (n < 0) {
        // Handle negative exponents if necessary.
        return 1 / power(x, -n);
    }
    
    double result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;  // If n is odd, multiply result by x
        }
        x *= x;  // Square x
        n /= 2;  // Divide n by 2
    }
    return result;
}

// Convert degrees to radians
double to_radians(double degrees)
{
    return degrees * (PI / 180.0);
}

// Approximate sine function using Taylor series expansion
double sin_approx(double x)
{
    // Convert x to radians and normalize to the range [-PI, PI] for better accuracy
    x = to_radians(x);
    x = fmod(x + PI, 2 * PI) - PI;
    
    return x - (power(x, 3))/FACTORIAL_3 + (power(x, 5))/FACTORIAL_5 - (power(x, 7))/FACTORIAL_7;
}

// Approximate cosine function using Taylor series expansion
double cos_approx(double x)
{
    // Convert x to radians and normalize to the range [-PI, PI] for better accuracy
    x = to_radians(x);
    x = fmod(x + PI, 2 * PI) - PI;
    
    return 1 - (power(x, 2))/FACTORIAL_2 + (power(x, 4))/FACTORIAL_4 - (power(x, 6))/FACTORIAL_6;
}
