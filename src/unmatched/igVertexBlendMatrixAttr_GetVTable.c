int igMatrix44f_SetIdentity();
int igObject_InitHeader();
extern int DAT_005226c0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[20]; char b[80]; };
int igVertexBlendMatrixAttr_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005226c0[0]);
    igMatrix44f_SetIdentity(&u.w[3]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
