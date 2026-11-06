int FUN_00195a90();
int igObject_InitHeader();
extern int DAT_0052aa10[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[12]; void *p[12]; char b[48]; };
int igModelViewMatrixBoneSelect_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&DAT_0052aa10[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052aa10[0]);
    FUN_00195a90(&u.w[0], 0);
    return temp_s0;
}

