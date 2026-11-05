/* 0x004831a0 — FUN_004831a0: a call followed by a memory barrier (sync). */
extern "C" {
void FUN_00076160(int);
void FUN_004831a0(int);
}
void FUN_004831a0(int a0)
{
    FUN_00076160(a0 & 0xffff);
    asm { sync }
}

