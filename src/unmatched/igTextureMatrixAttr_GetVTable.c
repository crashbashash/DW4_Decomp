struct F { int *vt; int w[23]; };
int igObject_InitHeader(struct F *);
int igMatrix44f_SetIdentity(void *);
extern int DAT_00522980[4];
extern void * DAT_00586dc8[4];
int igTextureMatrixAttr_GetVTable(void) {
    struct F f;

    igObject_InitHeader(&f);
    f.vt = &DAT_00522980[0];
    igMatrix44f_SetIdentity(&f.w[2]);
    return *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
