#include "csscolorparser.hpp"

#include <iostream>

using namespace CSSColorParser;

std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "rgba(" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << ", "
              << color.a << ")";
}

static bool errored = false;

void ASSERT_EQUAL(const Color& expected, const std::string& input) {
    const auto actual = parse(input);
    if (expected != actual) {
        errored = true;
        std::cerr << "\033[1mERROR!: expected " << expected << " != parsed " << actual
                  << " when parsing \"" << input << "\"\033[0m" << std::endl;
    } else {
        std::cerr << "Passed: " << actual << std::endl;
    }
}

void ASSERT_EQUAL(const Color& expected, const Color& actual) {
    if (expected != actual) {
        errored = true;
        std::cerr << "\033[1mERROR!: expected " << expected << " != actual " << actual << "\"\033[0m" << std::endl;
    } else {
        std::cerr << "Passed: " << actual << std::endl;
    }
}

int main() {
    try {
        ASSERT_EQUAL(Color{ 255, 128, 12, 0.5 }, " rgba (255, 128, 12, 0.5)");
        ASSERT_EQUAL(Color{ 255, 255, 255, 1 }, "#fff");
        ASSERT_EQUAL(Color{ 255, 0, 17, 1 }, "#ff0011");
        ASSERT_EQUAL(Color{ 106, 90, 205, 1 }, "slateblue");
        ASSERT_EQUAL(Color{ 0, 0, 0, 1 }, "blah");
        ASSERT_EQUAL(Color{ 0, 0, 0, 1 }, "ffffff");
        ASSERT_EQUAL(Color{ 226, 233, 233, 0.5 }, "hsla(900, 15%, 90%, 0.5)");
        ASSERT_EQUAL(Color{ 0, 0, 0, 1 }, "hsla(900, 15%, 90%)");
        ASSERT_EQUAL(Color{ 226, 233, 233, 1 }, "hsl(900, 15%, 90%)");
        ASSERT_EQUAL(Color{ 226, 233, 233, 1 }, "hsl(900, 0.15, 90%)"); // NOTE: not spec compliamt.

        // Out of range:
        ASSERT_EQUAL(Color{ 0, 0, 0, 1 }, "xxx");
        ASSERT_EQUAL(Color{ 255, 128, 12, 1 }, " rgba (255, 128, 12, 2)");
        ASSERT_EQUAL(Color{ 255, 128, 12, 1 }, " rgba (400, 128, 12, 2)");
        ASSERT_EQUAL(Color{ 255, 128, 12, 1 }, Color{ 255, 128, 12, 3 });
    } catch(std::exception& ex) {
        std::cerr << "EXCEPTION!: " << ex.what() << std::endl;
        return 2;
    }

    return errored ? 1 : 0;
}
