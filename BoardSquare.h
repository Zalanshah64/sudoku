#pragma once

#include <cstdint>
using std::size_t;
#include <iostream>
using std::ostream;
using std::cout;
#include <string>
using std::to_string;
#include <fstream>
using std::ofstream;

class BoardSquare {
    private:
    enum class SquareStatus : uint8_t {preloaded, testing, empty};

    size_t value = 0;
    SquareStatus status = SquareStatus::empty;

    public:

    BoardSquare();

    BoardSquare(const size_t val);

    void tryNum(const size_t val);

    void empty();

    bool operator!=(size_t val) const;
    bool operator==(size_t val) const;
    BoardSquare& operator=(size_t val);

    inline size_t getValue() const {
        return value;
    }

    bool occupied() const;

    friend inline ostream& operator<<(ostream &os, const BoardSquare &sq) {
        return os << ((sq.value != 0) ? to_string(sq.value) : "_");
    }
};