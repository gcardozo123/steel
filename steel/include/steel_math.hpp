#pragma once

#include <cmath>
#include <algorithm>

namespace Steel
{
namespace Math
{
constexpr long double Pi = 3.141592653589793238462643383279502884L;
constexpr long double PiOver2 = Pi / 2.0;
constexpr long double PiOver4 = Pi / 4.0;
constexpr long double TwoPi = Pi * 2.0;
constexpr long double Tau = TwoPi;

//TODO: for the following free functions, decide which ones should use `constexpr` instead of `inline`
template<typename T>
inline T Abs(T v) { return std::abs(v); }
template<typename T>
inline T Min(T a, T b) { return (a < b) ? a : b; }
template<typename T>
inline T Max(T a, T b) { return (a > b) ? a : b; }
template<typename T>
inline T Round(T v) { return std::round(v); }
template<typename T>
inline T Ceiling(T v) { return std::ceil(v); }
template<typename T>
inline T Floor(T v) { return std::floor(v); }
template<typename T>
inline T Sqrt(T v) { return std::sqrt(v); }
template<typename T>
inline T PowerI(T base, int exp) { return std::pow(base, exp); }
template<typename T>
inline T PowerF(T base, float exp) { return std::pow(base, exp); }

template<typename T>
inline float Clamp(T value, T min, T max)
{
    // First we check to see if we're greater than the max
    value = (value > max) ? max : value;
    // Then we check to see if we're less than the min.
    return (value < min) ? min : value;
}

// Calculates the absolute value of the difference of two values.
template<typename T>
inline T Distance (T a, T b) { return Abs(a - b); }

// Linearly interpolates between two values.
//  https://en.wikipedia.org/wiki/Linear_interpolation#Programming_language_support
inline float Lerp(float value1, float value2, float amount) { return value1 + (value2 - value1) * amount; }

// Linearly interpolates between two values.
// https://en.wikipedia.org/wiki/Linear_interpolation#Programming_language_support
inline float LerpPrecise(float value1, float value2, float amount) { return ((1 - amount) * value1) + (value2 * amount); }

inline float ToDegrees(float radians) { return (float)(radians * 57.295779513082320876798154814105); }
inline float ToRadians(float degrees) { return (float)(degrees * 0.017453292519943295769236907684886); }

// Reduces a given angle to a value between π and -π.
inline float WrapAngle(float angle)
{
    if ((angle > -Pi) && (angle <= Pi))
    {
        return angle;
    }
    angle = std::fmod(angle, TwoPi);
    if (angle <= -Pi)
    {
        return angle + TwoPi;
    }
    if (angle > Pi)
    {
        return angle - TwoPi;
    }
    return angle;
}

// Determines if value is powered by two.
inline bool IsPowerOfTwo(int value) { return (value > 0) && ((value & (value - 1)) == 0); }

inline bool IsAlmostEqual( float a, float b, float precision = 0.0001f ) { return abs( a - b ) <= precision; }

} //Math
} //Steel