int igMatrix44f_SetIdentity();
int igObject_InitHeader();
extern int DAT_00522d00[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[80]; };
int igTexGenMatrixAttr_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00522d00[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
