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

#define DEFAULT "\033[0m"
#define REDTEXT "\033[31m"
#define GREENTEXT "\033[32m"
#define BLUEBOLDTEXT "\033[1;34m"

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
        switch(sq.status) {
            case SquareStatus::preloaded:
                return os << BLUEBOLDTEXT << sq.value << DEFAULT;
            break;

            case SquareStatus::testing:
                return os << GREENTEXT << sq.value << DEFAULT;
            break;

            case SquareStatus::empty:
                return os << REDTEXT << "-" << DEFAULT;
            break;
        }
    }

    void inline print(ofstream &of) {
        if(value == 0) {
            of << "-";
        } else {
            of << value;
        }
    }
};