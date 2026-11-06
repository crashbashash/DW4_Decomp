int igObject_InitHeader();
extern int DAT_00533280[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[4]; void *p[4]; char b[16]; };
int igStringObj_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00533280[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

