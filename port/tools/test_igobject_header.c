/* dw4_object_init_header (retail igObject_InitHeader, 0x2fef20) was hand-written with byte arithmetic and is now
 * retargeted onto the decomp's authoritative igObject. It must give the same result as the previous version for
 * every incoming header word, and the result the retail function leaves: vtable word 0x52f0f0, header word 1,
 * nothing else touched. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dw4/object.h"

/* the implementation this replaced, verbatim */
static void reference_init_header(uint8_t *p)
{
    uint32_t v = 0x52f0f0u;
    uint32_t h;
    memcpy(p, &v, 4);
    memcpy(&h, p + 4, 4);
    h = (h & 0xff800000u) | 1u;
    memcpy(p + 4, &h, 4);
    p[6] &= 0x7fu;
    p[7] = 0;
}

int main(void)
{
    uint32_t seeds[] = {0u, 1u, 0x007fffffu, 0x00800000u, 0xff800000u, 0xffffffffu, 0x12345678u, 0x80000001u, 0x7f7f7f7fu};
    uint32_t i;
    int bad = 0;

    for (i = 0; i < sizeof seeds / sizeof seeds[0] + 4096; i++) {
        uint8_t a[16], b[16];
        uint32_t w0 = (i < sizeof seeds / sizeof seeds[0]) ? seeds[i] : i * 2654435761u;
        uint32_t w1 = (i < sizeof seeds / sizeof seeds[0]) ? seeds[i] : (i ^ 0xa5a5a5a5u) * 40503u;
        uint32_t vt, refs;
        memset(a, 0xcd, sizeof a);
        memcpy(a, &w0, 4);
        memcpy(a + 4, &w1, 4);
        memcpy(b, a, sizeof a);
        reference_init_header(a);
        dw4_object_init_header(b);
        memcpy(&vt, b, 4);
        memcpy(&refs, b + 4, 4);
        if (memcmp(a, b, sizeof a) != 0 || vt != 0x52f0f0u || refs != 1u) {
            printf("mismatch for header %08x %08x\n", w0, w1);
            bad++;
        }
    }
    if (bad) {
        printf("igobject header: %d mismatches\n", bad);
        return 1;
    }
    printf("igobject header: dw4_object_init_header matches the previous version and the retail result\n");
    return 0;
}
