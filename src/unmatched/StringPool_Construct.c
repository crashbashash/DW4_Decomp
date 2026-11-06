int Memory_GetAllocatorBySelector();
int Memory_GetDefaultAllocator();
int StringChunk_AllocateObject();
int StringChunk_Construct();
int StringTable_AllocateObject();
int StringTable_Construct();
extern int DAT_00587048[4];
extern unsigned char GPR_00554c14;
struct S { int f0; int f4; int f8; int f12; };

struct S *StringPool_Construct(struct S *arg0) {
    int var_v0;
    int var_v0_2;
    int var_v0_3;

    arg0->f0 = 0;
    arg0->f4 = 0;
    arg0->f8 = 0x4000;
    arg0->f12 = 0;
    var_v0 = arg0->f12;
    var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587048[0]);
    arg0->f12 = var_v0;
    if (arg0->f12 == 0) {
        arg0->f12 = Memory_GetDefaultAllocator();
    }
    var_v0_2 = StringTable_AllocateObject(0x18, arg0->f12);
    if (var_v0_2 != 0) {
        var_v0_2 = StringTable_Construct(var_v0_2, arg0, 0x400);
    }
    arg0->f0 = var_v0_2;
    var_v0_3 = StringChunk_AllocateObject(0x24, arg0->f12);
    if (var_v0_3 != 0) {
        var_v0_3 = StringChunk_Construct(var_v0_3, 0, arg0->f0, arg0->f8);
    }
    arg0->f4 = var_v0_3;
    return arg0;
}
