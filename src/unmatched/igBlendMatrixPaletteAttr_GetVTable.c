int igObject_InitHeader();
extern int DAT_00524110[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igBlendMatrixPaletteAttr_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524110[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
