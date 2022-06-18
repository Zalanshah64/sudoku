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

void BoardSquare::establish(const size_t val) {
    value = val;
    status = SquareStatus::preloaded;
}

void BoardSquare::tryIncorrect(const size_t val) {
    value = val;
    status = SquareStatus::incorrect;
}

void BoardSquare::breakSquare() {
    status = (status == SquareStatus::preloaded) ? SquareStatus::incorrectPreloaded : SquareStatus::incorrect;
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