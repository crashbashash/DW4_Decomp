struct O { int w0; int w4; };
int List_LowerBound();
struct O *DumpRegion_Init();
int DumpRegion_SetAnnotation();
int DumpRegion_SetPoolName();
struct O *DumpRegion_Allocate();
int SystemAllocatorBase_CollectHardwareRegions();
int List_InsertWords();
void DumpRegion_CompareStart(void);
extern int DAT_004ffd98[4];
extern int DAT_004ffda8[4];
extern int DAT_004ffdb8[4];
extern char DAT_70000000[];
extern char DAT_00004000[];
void SystemAllocator_CollectHardwareRegions(int arg0, int arg1) {
    struct O * sp2C;
    struct O *v;

    SystemAllocatorBase_CollectHardwareRegions(arg0);
    v = DumpRegion_Allocate(0xA8);
    if (v != 0) {
        v = DumpRegion_Init(v);
    }
    sp2C = v;
    v->w0 = 0;
    sp2C->w4 = 0x02000000;
    DumpRegion_SetAnnotation(sp2C, &DAT_004ffd98[0]);
    DumpRegion_SetPoolName(sp2C, &DAT_004ffda8[0]);
    List_InsertWords(arg1, List_LowerBound(arg1, &sp2C, DumpRegion_CompareStart), 1, &sp2C);
    v = DumpRegion_Allocate(0xA8);
    if (v != 0) {
        v = DumpRegion_Init(v);
    }
    sp2C = v;
    v->w0 = (int)&DAT_70000000[0];
    sp2C->w4 = (int)&DAT_00004000[0];
    DumpRegion_SetAnnotation(sp2C, &DAT_004ffdb8[0]);
    DumpRegion_SetPoolName(sp2C, &DAT_004ffda8[0]);
    List_InsertWords(arg1, List_LowerBound(arg1, &sp2C, DumpRegion_CompareStart), 1, &sp2C);
}
