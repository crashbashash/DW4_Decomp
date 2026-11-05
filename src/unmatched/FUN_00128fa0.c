/* 0x00128fa0 — FUN_00128fa0 (100 bytes). Steps the 64-bit linear congruential generator kept in the reent block and returns its top 31 bits (newlib rand shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Reent {
    char f0[168];
    unsigned long randomNext;
} Reent;

extern Reent *DAT_004854a0;

int FUN_00128fa0(void) {
    DAT_004854a0->randomNext = DAT_004854a0->randomNext * 6364136223846793005UL + 1;
    return (int)((DAT_004854a0->randomNext >> 32) & 0x7fffffff);
}
