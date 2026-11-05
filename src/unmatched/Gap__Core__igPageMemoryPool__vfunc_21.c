int FUN_002cd7c0();
int FUN_00325810();
int FUN_002f0040();
int Memory_GetDefaultAllocator();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int Gap__Core__igPageMemoryPool__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        FUN_002cd7c0();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = FUN_002f0040(0x110, 0, Memory_GetDefaultAllocator());
    if (temp_v0 != 0) {
        temp_v0 = FUN_00325810(temp_v0, arg0);
    }
    return temp_v0;
}
