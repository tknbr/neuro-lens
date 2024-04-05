
/**
 * Converts an angle from degrees to radians.
 * 
 * Since trigonometric functions in the Taylor series expansion are calculated in radians,
 * this function provides a utility for converting angles from degrees (a common input format) 
 * to radians (required for mathematical computations).
 *
 * @param degrees The angle in degrees to be converted.
 * @return The angle in radians.
 */
double to_radians(double degrees);

/**
 * Approximates the sine of an angle, given in radians, using the Taylor series expansion.
 * 
 * This function provides a simplified approximation of the sine function for small angles or
 * applications where high precision is not critical. It uses the first four terms of the 
 * Taylor series expansion for sine.
 * 
 * @param x The radians for which to approximate the sine. For improved accuracy, 
 *          the angle should be normalized to the range [-PI, PI].
 * @return An approximation of the sine of the input angle.
 * 
 * Note: The accuracy of this approximation decreases as the angle moves away from 0.
 */
double sin_approx(double x);

/**
 * Approximates the cosine of an angle, given in radians, using the Taylor series expansion.
 * 
 * Similar to sin_approx, this function provides an approximation of the cosine function using 
 * the first four terms of the Taylor series expansion for cosine. It is suitable for small angles
 * or when precise accuracy is not essential.
 *
 * @param x The angle in radians for which to approximate the cosine. For improved accuracy, 
 *          the angle should be normalized to the range [-PI, PI].
 * @return An approximation of the cosine of the input angle.
 * 
 * Note: As with sin_approx, the precision of this approximation diminishes for angles far from 0.
 */
double cos_approx(double x);
