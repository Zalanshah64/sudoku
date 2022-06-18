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
#define WHITETEXT "\033[37m"
#define REDBACKGROUND "\033[41m"

class BoardSquare {
    private:
    enum class SquareStatus : uint8_t {empty, preloaded, testing, incorrectPreloaded, incorrect};

    size_t value = 0;
    SquareStatus status = SquareStatus::empty;

    public:

    BoardSquare();

    BoardSquare(const size_t val);

    void tryNum(const size_t val);
    void establish(const size_t val);
    void tryIncorrect(const size_t val);
    void breakSquare();

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

            case SquareStatus::incorrect:
            case SquareStatus::incorrectPreloaded:
            return os << REDBACKGROUND << WHITETEXT << sq.value << DEFAULT;
            break;
        }
    }

    bool inline incorrect() {
        return status > SquareStatus::testing;
    }

    void inline print(ofstream &of) {
        if(value == 0) {
            of << "-";
        } else {
            of << value;
        }
    }
};