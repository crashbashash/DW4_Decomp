/* Returns the low 32 bits of the 64-bit value from FUN_00275fd8. */
extern long long FUN_00275fd8(void);

int FUN_00276060(void) {
    return (int)(FUN_00275fd8() & 0xFFFFFFFF);
}
