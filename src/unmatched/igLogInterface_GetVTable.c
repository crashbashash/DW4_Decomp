int igObject_InitHeader();
extern int DAT_0052bfa0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[12]; void *p[12]; char b[48]; };
int igLogInterface_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052bfa0[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

