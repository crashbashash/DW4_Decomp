typedef struct X { char pad[4]; int f4; int f8; } X;
typedef struct A { char pad[52]; int f52; char pad2[416]; int f472; int f476; } A;
X *FUN_001356b0();
X *FUN_001a3590();
int FUN_001b1030();
int FUN_001b1100();
int FUN_001e07a0();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
int FUN_001bce40(A *arg0, int *arg1) {
    X *temp_s2;
    X *temp_v0;
    int temp_s0;
    int temp_s1;
    temp_s0 = arg0->f52;
    *(char *)((char *)arg0 + 496) = 1;
    temp_s2 = FUN_001356b0(igObject_GetAllocator());
    temp_v0 = FUN_001a3590(igObject_GetAllocator(arg0));
    temp_v0->f8 = arg1[8];
    ObjectList_AppendRetained(arg0->f472, temp_s2);
    ObjectList_AppendRetained(arg0->f476, temp_v0);
    temp_s2->f4 = temp_s2->f4 - 1;
    if (((unsigned long long) ((long long) temp_s2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s2);
    }
    temp_v0->f4 = temp_v0->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    FUN_001b1030(temp_s0, temp_s2);
    temp_s1 = FUN_001e07a0(arg0, arg1);
    FUN_001b1100(temp_s0, temp_s2);
    if (temp_s1 == 2) {
        return 2;
    }
    return 0;
}
