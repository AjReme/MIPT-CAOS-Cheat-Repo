#include <limits.h>
#include <inttypes.h>

uint16_t satsum(uint16_t x, uint16_t y)
{
    uint16_t sm = x + y;
    uint16_t ret = ~((uint16_t)0);
    return sm < x ? ret : sm;
}
