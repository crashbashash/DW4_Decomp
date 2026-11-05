/* 0x002c5240 - igExternalIndexedEntry_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py. */
int FUN_0014f4e0();
int FUN_0019c840();
int igObject_InitHeader();
extern int DAT_005302b0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[16]; void *p[16]; char b[64]; };
int igExternalIndexedEntry_GetVTable(void) {
    union U u;
    int temp_s1;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_005302b0[0]);
    u.w[9] = 0;
    u.w[11] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005302b0[0]);
    FUN_0019c840(&u.w[11], -1);
    FUN_0019c840(&u.w[9], -1);
    FUN_0014f4e0(&u.w[0], 0);
    return temp_s1;
}

