#include <stdio.h>
#include <stdint.h>

#include "palin.h"

int palindrome(uint32_t x) {
    uint32_t base_mask = 0xF;
    uint32_t base_x = x;
    uint32_t right_side = 0x0;
    uint32_t left_side = 0x0;
    x = x>>16;
    
    for (unsigned int i=0; i<4; i++) {
        uint32_t right_mask = x & base_mask;
        uint32_t left_mask = base_x & base_mask;
        right_side = (right_side << 4) | right_mask;
        left_side = (left_side << 4) | left_mask;
        x = x >> 4;
        base_x = base_x>>4;
    }
    right_side = right_side>>16;
    uint32_t result = left_side | right_side;
    if(result == base_x)
        return 1;
    else 
        return 0;
}
