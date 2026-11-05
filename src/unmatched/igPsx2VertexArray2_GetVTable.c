int FUN_0014a910();
int igObject_InitHeader();
extern int DAT_00525120[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igPsx2VertexArray2_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&DAT_00525120[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00525120[0];
    FUN_0014a910(u.b, 0);
    return temp_s0;
}
