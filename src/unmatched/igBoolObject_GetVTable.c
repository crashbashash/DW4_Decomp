struct O { int *vt; char post[12]; };
int igObject_InitHeader(void *);
extern int DAT_0052b9b0[4];
extern char *DAT_00586dc8[4];
int igBoolObject_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_0052b9b0;
    return *(int *)((char *)&o.vt + *(int *)(DAT_00586dc8[0] + 916));
}
