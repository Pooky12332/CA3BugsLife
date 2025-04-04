#include "Util.h"
#include <string>

using namespace std;

// Util
// Returns a string of direction
string getDirecName(Direction direction) {
    switch (direction) {
        case North: return "North";
        case East: return "East";
        case South: return "South";
        case West: return "West";
        default: return "";
    }
}