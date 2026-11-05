/* 0x00140f40 — FUN_00140f40. m2c draft, symbol; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern char DAT_004d5e30[];
int FUN_00140e90();
int FUN_00306e50();
extern void * DAT_00586dc8[4];
void FUN_00140f40(void) {
    unsigned char sp1F;

    sp1F = 0;
    FUN_00306e50(*(int *)((char *)DAT_00586dc8[0] + 56), 7, DAT_004d5e30, &sp1F, 0, 0);
    FUN_00140e90(sp1F);
}
