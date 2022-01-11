#pragma once 

#include <cstdint>
#include <cstddef>
#include <string_view>
#include <array>

struct bf_memory 
{
    std::uint8_t* mem = nullptr;

    std::size_t allocated{};
    std::size_t size{};

    constexpr void resize(std::size_t new_size) noexcept
    {
        auto* old = mem;

        mem = new std::uint8_t[new_size] {};
        
        std::fill(&mem[0], &mem[new_size - 1], 0);

        if (old)
        {
            for (std::size_t i = 0; i < size; i++)
                mem[i] = old[i];
        
            delete[] old;
        }

        allocated = new_size;
    }

    constexpr bf_memory() noexcept
    {
        resize(16);
    }

    constexpr ~bf_memory() noexcept
    {
        if (mem)
            delete[] mem;
    }

    [[nodiscard]] constexpr std::size_t length() const noexcept
    {
        return size;
    }

    [[nodiscard]] constexpr std::uint8_t& operator[](const std::size_t i) noexcept
    {
        if (i >= allocated)
            resize(i + 1);
        
        if (i >= size)
            size = i + 1;

        return mem[i];
    }
    
};

struct loop_queue 
{
    std::size_t* mem = nullptr;

    std::size_t allocated{};
    std::size_t size{};

    constexpr void resize(std::size_t new_size) noexcept
    {
        auto* old = mem;

        mem = new std::size_t[new_size];
        
        std::fill(&mem[0], &mem[new_size - 1], 0);

        if (old)
        {
            for (std::size_t i = 0; i < size; i++)
                mem[i] = old[i];
        
            delete[] old;
        }

        allocated = new_size;
    }

    constexpr loop_queue() noexcept
    {
        resize(16);
    }

    constexpr ~loop_queue() noexcept
    {
        if (mem)
            delete[] mem;
    }

    [[nodiscard]] constexpr std::size_t length() const noexcept
    {
        return size;
    }

    constexpr void push(const std::size_t idx) noexcept
    {
        if ((size + 1) >= allocated)
            resize(allocated + 2);
        
        mem[size++] = idx;
    }

    constexpr void pop() noexcept 
    {
        if (!size)
            return;

        --size;
    }

    [[nodiscard]] constexpr std::size_t end() noexcept 
    {
        if (!size)
            return 0;
        
        return mem[size - 1];
    }
    
};

template<std::size_t out_size = 2048>
[[nodiscard]] consteval std::array<char, out_size> brainfuck(const std::string_view program, const std::string_view input)
{
    bf_memory memory{};
    bf_memory output{};

    std::size_t i{}, m{}, input_l{};

    loop_queue loop{};

    while (i < program.length())
    {
        char ins = program[i++];
        
        if (ins == '>')
            m++;
        else if (ins == '<')
            m--;
        else if (ins == '+')
            memory[m]++;
        else if (ins == '-')
            memory[m]--;
        else if (ins == '.')
            output[output.length()] = memory[m];
        else if (ins == ',')
            memory[m] = input_l >= input.length() ? 0 : input[input_l++];
        else if (ins == '[')
        {
            if (memory[m])
                loop.push(i);
            else
                while (program[++i] != ']');
        }
        else if (ins == ']')
        {
            if (memory[m])
                i = loop.end();
            else 
                loop.pop();
        }

    }

    std::array<char, out_size> out{};
    
    auto length = std::min(output.length(), out_size);

    for (std::size_t n = 0; n < length; ++n)
        out[n] = output[n];

    out[length] = 0;

    return out;
}