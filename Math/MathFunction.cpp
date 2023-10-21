#include <stdint.h>

uint32_t Exponent(uint32_t base, uint32_t index)
{
    uint32_t result = 1;
    for (uint32_t i = 0; i < index; i++) {
        result = result * base;
    }
    return result;
}