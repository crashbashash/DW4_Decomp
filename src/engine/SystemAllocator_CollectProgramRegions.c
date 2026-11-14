struct O { int w0; int w4; };
int List_LowerBound();
struct O *DumpRegion_Init();
int DumpRegion_SetAnnotation();
int DumpRegion_SetPoolName();
struct O *DumpRegion_Allocate();
int SystemAllocatorBase_CollectProgramRegions();
int List_InsertWords();
void DumpRegion_CompareStart(void);
extern int DAT_004ffa98[4];
extern int DAT_004ffdd0[4];
extern int DAT_004ffdf0[4];
extern int DAT_004ffe00[4];
extern char __ctors_start__[];
extern char DAT_00522480[];
extern char __exception_table_start__[];
extern char DAT_00554974[];
extern char DAT_0000050d[];
void SystemAllocator_CollectProgramRegions(int arg0, int arg1) {
    struct O * sp3C;
    struct O *v;
    char *mid;

    SystemAllocatorBase_CollectProgramRegions();
    v = DumpRegion_Allocate(0xA8);
    if (v != 0) {
        v = DumpRegion_Init(v);
    }
    sp3C = v;
    v->w0 = (int)&__ctors_start__[0];
    mid = DAT_00522480;
    sp3C->w4 = (int)(mid - __ctors_start__);
    DumpRegion_SetAnnotation(sp3C, &DAT_004ffdd0[0]);
    DumpRegion_SetPoolName(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, List_LowerBound(arg1, &sp3C, DumpRegion_CompareStart), 1, &sp3C);
    v = DumpRegion_Allocate(0xA8);
    if (v != 0) {
        v = DumpRegion_Init(v);
    }
    sp3C = v;
    v->w0 = (int)mid;
    sp3C->w4 = (int)(__exception_table_start__ - mid);
    DumpRegion_SetAnnotation(sp3C, &DAT_004ffdf0[0]);
    DumpRegion_SetPoolName(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, List_LowerBound(arg1, &sp3C, DumpRegion_CompareStart), 1, &sp3C);
    v = DumpRegion_Allocate(0xA8);
    if (v != 0) {
        v = DumpRegion_Init(v);
    }
    sp3C = v;
    v->w0 = (int)&DAT_00554974[0];
    sp3C->w4 = (int)&DAT_0000050d[0];
    DumpRegion_SetAnnotation(sp3C, &DAT_004ffe00[0]);
    DumpRegion_SetPoolName(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, List_LowerBound(arg1, &sp3C, DumpRegion_CompareStart), 1, &sp3C);
}
