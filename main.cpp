#include <iostream>
#include "Bus.h"
#include "c6502.h"
#include <string>
#include <bitset>
#include <sstream>

void printRegisters(c6502 &cpu) {
    std::cout << "Registers" << std::endl;
    printf("A: %02hhx ", cpu.a);
    printf("X: %02hhx ", cpu.x);
    printf("Y: %02hhx ", cpu.y);
    std::cout << std::endl;
    std::cout << std::endl;
}

void printPointers(c6502 &cpu) {
    std::cout << "Pointers:" << std::endl;
    printf("Stkp: %02hhx ", (unsigned char)cpu.stkp);
    std::cout << "PC: " <<std::hex << (unsigned int)cpu.pc << std::endl;
    std::cout << std::endl;
}

void printRam(Bus &bus, uint16_t begin, uint16_t end) {
    std::cout << "RAM:" << std::endl;
    for (int i = begin; i < end; i++) {
        if (i % 16 == 0) {
            std::cout << std::hex << (unsigned int)i;
            std::cout << ": ";
        }
        printf("%02hhx ", bus.ram[i]);
        if ((i + 1) % 16 == 0)
            std::cout << std::endl;
    }
}

void printStatusFlags(c6502 &cpu) {
    std::cout << "Status:" << std::endl;
    std::bitset<8> x(cpu.status);
    std::cout << "NVUBDIZC" << std::endl;
    std::cout << x << std::endl << std::endl;
}

void printState(Bus &bus) {
    std::cout << "6502 Emulation" << std::endl << std::endl;

    printRegisters(bus.cpu);
    printPointers(bus.cpu);
    printStatusFlags(bus.cpu);
    printRam(bus, 0x0200, 0x0220);
}

int main() {
    Bus bus = Bus();
    std::stringstream ss;
    ss << "a2 00 a0 00 8a 99 00 02 48 e8 c8 c0 10 d0 f5 68 99 00 02 c8 c0 20 d0 f7";
    //ss << "a0 40 a9 10 c9 10 e9 10";
    uint16_t nOffset = 0x0600;
    while (!ss.eof())
    {
        std::string b;
        ss >> b;
        bus.ram[nOffset++] = (uint8_t)std::stoul(b, nullptr, 16);
    }
    bus.ram[0xFFFC] = 0x00;
	bus.ram[0xFFFD] = 0x06;
    bus.cpu.reset();
    while(true) {
        printState(bus);
        std::getchar();
        bus.cpu.step();
    }
        

    return 0;
}