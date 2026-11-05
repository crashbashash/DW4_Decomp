typedef struct RT { int w0; int references; char pad[20]; char f28; } RT;
RT *FUN_001a90f0();
int FUN_00306e50();
int Memory_GetAllocatorBySelector();
RT *igAnimationCombinerBoneInfoPool_Create();
RT *igAnimationStatePool_Create();
int igObject_Destroy(RT *);
extern int DAT_004e44e0[4];
extern RT * DAT_00562528[4];
extern RT * DAT_00562540[4];
extern RT * DAT_00562558[4];
extern int * DAT_00586dc8[4];
extern int DAT_00587038[4];
extern int GPR_00554b84;

void FUN_001abca0(void) {
    int s0;
    RT *t;
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562528[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    DAT_00562528[0] = igAnimationCombinerBoneInfoPool_Create(s0);
    DAT_00562528[0]->f28 = 0;
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562540[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    DAT_00562540[0] = igAnimationStatePool_Create(s0);
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562558[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    DAT_00562558[0] = FUN_001a90f0(s0);
    FUN_00306e50(*(int *)((char *)(DAT_00586dc8[0]) + 56), 7, &DAT_004e44e0[0], &GPR_00554b84, 0, 0);
}
