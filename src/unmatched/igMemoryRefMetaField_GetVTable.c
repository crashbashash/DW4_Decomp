int FUN_0014ec50();
int FUN_002bf5e0();
int StringRef_Destruct_00130720();
int igMemoryRefMetaField_Init();
extern int DAT_00532a50[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[80]; };
int igMemoryRefMetaField_GetVTable(void) {
    union U u;
    int temp_s0;

    igMemoryRefMetaField_Init(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00532a50[0];
    StringRef_Destruct_00130720(&u.b[76], -1);
    FUN_0014ec50(&u.b[72], -1);
    FUN_002bf5e0(u.b, 0);
    return temp_s0;
}
