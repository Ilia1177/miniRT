#include <miniRT_bonus.h>

t_vec4 random_vec4(float magnitude)
{
    // Generate two random numbers in [0, 1)
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;

    // Convert to spherical coordinates
    double theta = 2 * M_PI * u1;         // Azimuthal angle [0, 2π)
    double phi = acos(2 * u2 - 1.0);      // Polar angle [0, π]

    // Compute Cartesian coordinates on the unit sphere
    double sin_phi = sin(phi);
    double x = sin_phi * cos(theta);
    double y = sin_phi * sin(theta);
    double z = cos(phi);

    // Scale to the desired magnitude
    t_vec4 vec;
    vec.x = x * magnitude;
    vec.y = y * magnitude;
    vec.z = z * magnitude;
    return vec;
}
