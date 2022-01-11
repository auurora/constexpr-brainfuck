# C++20 Constant Expression Brainfuck Interpreter

This interprets brainfuck at compile time in C++20 by leveraging the now added constexpr new compile time allocation.

## Usage

```cpp
#include "brainfuck.hpp"

int main()
{
  using namespace std::literals::string_view_literals;
  
  constexpr auto result = brainfuck("program"sv, "input"sv);
  /* brainfuck returns a std::array<char, out_size> where out_size is by default set to 2048 */
  /* you may extend the output buffer by passing it as a template argument: brainfuck<99999>(...); */
}
```

#### Limitations 

The output std::array size is not dynamically calculated, 
you could probably do this by running the program twice and using the first to retrieve the size.
If I recall correctly you cannot use auto and add the output length in the std::array parameter and I wasn't going to bother making the code run twice
