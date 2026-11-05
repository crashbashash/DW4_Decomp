/* 0x001a4fd0 - igBillboard_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py. */
int FUN_00142d10();
int FUN_00195a90();
int igObject_InitHeader();
extern int DAT_0052a2a0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[16]; void *p[16]; char b[64]; };
int igBillboard_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&DAT_0052a2a0[0]);
    u.w[15] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a2a0[0]);
    FUN_00142d10(&u.w[15], -1);
    FUN_00195a90(&u.w[0], 0);
    return temp_s0;
}

