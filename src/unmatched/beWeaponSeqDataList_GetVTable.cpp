union U { int vt; char b[32]; };
extern "C" {
int igObject_InitHeader(char *);
extern int DAT_00539ce0[4];
extern void * DAT_00586dc8[4];
int beWeaponSeqDataList_GetVTable(void);
}
int beWeaponSeqDataList_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539ce0[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
