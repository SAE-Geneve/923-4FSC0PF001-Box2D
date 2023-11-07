#pragma once
#include "SFML/Graphics.hpp"

#define MATH_DEFINES_DEFINED
#define USE_MATH_DEFINES // for C++
#include <cmath>

#define M_PI 3.14159265358979323846
constexpr float kEpsilon = 0.0001f;
constexpr float kPixelsMetersRatio = 100.0f;

inline float DotProduct(const sf::Vector2f vec1, const sf::Vector2f vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
};

inline float Det(const sf::Vector2f vec1, const sf::Vector2f vec2) {
    return vec1.x * vec2.y - vec1.y * vec2.x;
};

inline float VecLength(const sf::Vector2f vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
};

inline float VecDistance(const sf::Vector2f p1, const sf::Vector2f p2) {
    return std::sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
};

inline float VecAngle(const sf::Vector2f vec1, const sf::Vector2f vec2) {
    return std::atan2(Det(vec1, vec2), DotProduct(vec1, vec2));
};

inline float DegToRad(const float degrees) {
    return (degrees * M_PI / 180.0f);
};

inline float RadToDeg(const float radians) {
    return (radians / M_PI * 180.0f);
};


inline b2Vec2 PixelsToMeters(const sf::Vector2f pixels)
{
    return {pixels.x / kPixelsMetersRatio, 1.0f * pixels.y / kPixelsMetersRatio};
}

inline b2Vec2  PixelsToMeters(const sf::Vector2u pixels)
{
    return {pixels.x / kPixelsMetersRatio, 1.0f * pixels.y / kPixelsMetersRatio};
}

inline float  PixelsToMeters(const float pixels)
{
    return pixels / kPixelsMetersRatio;
}

inline sf::Vector2f MetersToPixels(const b2Vec2 meters)
{
    return {meters.x * kPixelsMetersRatio, 1.0f * meters.y * kPixelsMetersRatio};
}



