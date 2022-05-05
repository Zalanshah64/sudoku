#include "BoardSquare.h"
#include <cstdint>
using std::size_t;

BoardSquare::BoardSquare() {
    value = 0;
    status = SquareStatus::empty;
}

BoardSquare::BoardSquare(const size_t val) {
    value = val;
    status = SquareStatus::preloaded;
}

void BoardSquare::tryNum(const size_t val) {
    value = val;
    status = SquareStatus::testing;
}

void BoardSquare::empty() {
    value = 0;
    status = SquareStatus::empty;
}

bool BoardSquare::operator!=(size_t val) const {
    return value != val;
}

bool BoardSquare::operator==(size_t val) const {
    return value == val;
}

BoardSquare& BoardSquare::operator=(size_t val) {
    value = val;
    status = SquareStatus::preloaded;
    return *this;
}

bool BoardSquare::occupied() const {
    return status != SquareStatus::empty;
}