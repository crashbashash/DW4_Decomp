extern "C" {
typedef struct Obj { int w0; unsigned refs; } Obj;
int FUN_0010b9c0(int);
int FUN_00264af0();
int FUN_00280d20();
int FUN_00294df8();
int FUN_00332d20(int);
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorByName(int *);
int RemoveIntcHandler(int, int);
int igObject_Destroy(Obj *);
extern int DAT_004ffe68[4];
extern int DAT_005873a8[4];
extern int DAT_005873b8[4];
extern int DAT_005873c0[4];
extern Obj *DAT_005875e0[4];
extern Obj *DAT_00587620[4];
void FUN_00332530(void) {
    int temp_s0;
    Obj *o;

    FUN_00332d20(0);
    o = DAT_00587620[0];
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00587620[0] = 0;
    o = DAT_005875e0[0];
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_005875e0[0] = 0;
    FUN_00294df8();
    FUN_00280d20();
    FUN_0010b9c0(2);
    RemoveIntcHandler(2, DAT_005873c0[0]);
    temp_s0 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if (DAT_005873a8[0] != 0) {
        Memory_FreeBufferWithAllocator(DAT_005873a8[0], temp_s0);
        DAT_005873a8[0] = 0;
    }
    if (DAT_005873b8[0] != 0) {
        Memory_FreeBufferWithAllocator(DAT_005873b8[0], temp_s0);
        DAT_005873b8[0] = 0;
    }
    FUN_00264af0();
}
}
