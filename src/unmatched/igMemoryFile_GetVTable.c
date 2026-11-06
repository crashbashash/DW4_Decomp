int FUN_002c0790();
int igObject_InitHeader();
extern int DAT_0052f7b0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[16]; void *p[16]; char b[64]; };
int igMemoryFile_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[10] = 0;
    u.w[0] = (int)(&DAT_0052f7b0[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052f7b0[0]);
    FUN_002c0790(&u.w[0], 0);
    return temp_s0;
}

