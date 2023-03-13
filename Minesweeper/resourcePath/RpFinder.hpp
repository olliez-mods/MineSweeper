#ifndef RpFinder_hpp
#define RpFinder_hpp

#include <string>

#ifdef __APPLE__
#include "AppleResPathFinder.hpp"
#endif

namespace sfas
{
void setResPath(std::string nP);
std::string rp();

}

#endif
