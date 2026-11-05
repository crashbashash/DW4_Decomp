/* 0x001ef4c0 - FUN_001ef4c0. volatile hardware-register read-modify-writes, forwarded argument, asm sync/ei idiom Verified byte-identical by tools/verify.py. */
extern "C" {
int FUN_001ef280(int, int);
int FUN_001ef4c0(int);
extern int DAT_00568f60[4];
extern volatile int DAT_0056d670[4];
extern volatile int DAT_0056d678[4];
}
int FUN_001ef4c0(int arg0) {
    if (DAT_00568f60[0] != 0) {
        DAT_0056d670[0] &= ~0x20;
        DAT_0056d678[0] &= ~0x20;
        FUN_001ef280(arg0, DAT_00568f60[0]);
    }
    asm { sync }
    asm { ei }
    return 0;
}
