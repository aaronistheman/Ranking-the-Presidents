#ifndef PRESIDENTS_UTILITY_HPP
#define PRESIDENTS_UTILITY_HPP

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#include <Presidents/Utility.inl>
#endif // PRESIDENTS_UTILITY_HPP