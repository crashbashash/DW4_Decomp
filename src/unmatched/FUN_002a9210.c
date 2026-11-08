extern int WaitSema(int s);
extern int SignalSema(int s);
extern void FUN_002a8c08(int a);
extern void FUN_002a8ba0(int a);
#define REG(a) (*(volatile int *)(a))
typedef struct { char pad[28]; int r28, r32, r36, r40, r44, r48, r52, r56, r60; int sema; int f68; } B;
int FUN_002a9210(B *b) {
    WaitSema(b->sema);
    b->f68 = 0;
    FUN_002a8c08(5);
    b->r28 = REG(0x1000B410);
    b->r32 = REG(0x1000B430);
    b->r36 = REG(0x1000B420);
    b->r40 = REG(0x1000B400);
    while (REG(0x10002010) & 0xF0) {
    }
    FUN_002a8ba0(0);
    b->r44 = REG(0x1000B010);
    b->r48 = REG(0x1000B020);
    b->r52 = REG(0x1000B000);
    b->r56 = REG(0x10002020);
    b->r60 = REG(0x10002010);
    SignalSema(b->sema);
    return 1;
}
