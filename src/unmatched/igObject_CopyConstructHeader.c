typedef struct H { int vt; char pad[2]; unsigned char lo : 7; unsigned char hi : 1; unsigned char b7; } H;
int Memory_FindOwningAllocator();
char igAllocator_EncodeIndex();
int igObject_GetAllocationBase();
int igObject_InitHeader();
extern int DAT_0052f0f0[4];
extern unsigned char *DAT_00586dc8[4];
H *igObject_CopyConstructHeader(H *arg0, H *arg1) {
    arg0->vt = (int)&DAT_0052f0f0[0];
    if (arg0 != 0) {
        igObject_InitHeader(arg0);
    }
    arg0->hi = arg1->hi;
    if (*DAT_00586dc8[0] != 0) {
        arg0->b7 = igAllocator_EncodeIndex(Memory_FindOwningAllocator(igObject_GetAllocationBase(arg0)));
    }
    return arg0;
}
