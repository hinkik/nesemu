#pragma once
#include <cstdint>
#include "c6502.h"
#include <array>

class Bus
{
public:
    Bus();
    ~Bus();

public:
    c6502 cpu;
    std::array<uint8_t, 64 * 1024> ram;

public:
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
};