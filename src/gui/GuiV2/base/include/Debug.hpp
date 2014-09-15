
#ifndef HPP_DEBUG
#define HPP_DEBUG

#define DEBUG 1

#if DEBUG

#include <cassert>
#include <iostream>

#define debug(x)    std::cerr << x;

#else

#define assert(x)
#define debug(x)

#endif

#endif

