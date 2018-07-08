#include "lfsr.h"

void GLFSR_init(lfsr_t *glfsr, lfsr_data_t polynom, lfsr_data_t seed_value) {
    lfsr_data_t seed_mask;
    unsigned int shift = 8 * sizeof (lfsr_data_t) - 1;

    glfsr->polynomial = polynom | 1;
    glfsr->data = seed_value;

    seed_mask = 1;
    seed_mask <<= shift;

    while (shift--) {
        if (polynom & seed_mask) {
            glfsr->mask = seed_mask;
            break;
        }
        seed_mask >>= 1;
    }
    return;
}

unsigned char GLFSR_next(lfsr_t *glfsr) {
    unsigned char retval = 0;

    glfsr->data <<= 1;

    if (glfsr->data & glfsr->mask) {
        retval = 1;
        glfsr->data ^= glfsr->polynomial;
    }

    return retval ;
}
