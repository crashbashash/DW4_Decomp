/* Steps the 64-bit linear congruential generator kept in the reent block and returns its top 31
 * bits. */
typedef struct Reent {
    char f0[168];
    unsigned long randomNext;
} Reent;

extern Reent *DAT_004854a0;

int FUN_00128fa0(void) {
    DAT_004854a0->randomNext = DAT_004854a0->randomNext * 6364136223846793005UL + 1;
    return (int)((DAT_004854a0->randomNext >> 32) & 0x7fffffff);
}
