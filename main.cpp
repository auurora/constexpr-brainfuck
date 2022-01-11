#include "brainfuck.hpp"

#include <iostream>

int main()
{
    using namespace std::literals::string_view_literals;

    constexpr auto a = brainfuck("--[----->+<]>-----.--[--->+<]>..---.---.+++.+++[->+++<]>++.-[->+++<]>.-[--->++<]>-.++++++++++.+[---->+<]>+++.+[->+++<]>.++++++++++++..---."sv, ""sv);

    std::cout << a.data() << '\n';
}