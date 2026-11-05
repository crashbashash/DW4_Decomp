struct W { int *vt; int f[19]; };
int igObject_InitHeader(struct W *);
int igMatrix44f_SetIdentity(void *);
extern int DAT_00542960[4];
extern char *DAT_00586dc8[4];
int igViewMode_GetVTable(void) {
    struct W o;
    igObject_InitHeader(&o);
    o.vt = DAT_00542960;
    igMatrix44f_SetIdentity(&o.f[2]);
    return *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
}
