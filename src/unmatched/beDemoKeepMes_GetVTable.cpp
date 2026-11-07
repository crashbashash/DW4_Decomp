union U { int vt; char b[48]; };
extern "C" {
int StringRef_Destruct_00130720(char *, int);
int igObject_InitHeader(char *);
extern int DAT_00535610[4];
extern void * DAT_00586dc8[4];
int beDemoKeepMes_GetVTable(void);
}
int beDemoKeepMes_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00535610[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535610[0];
    StringRef_Destruct_00130720(&u.b[40], -1);
    StringRef_Destruct_00130720(&u.b[36], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    StringRef_Destruct_00130720(&u.b[24], -1);
    return r;
}
