int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052c400[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int igIterateField_GetVTable(void) {
    union U u;
    int t;
    char *ps;
    int *p;
    int *q;
    int v;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052c400[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052c400[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return t;
}
