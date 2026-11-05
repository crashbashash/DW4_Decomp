int igMatrix44f_SetIdentity();
int igObject_InitHeader();
extern int DAT_005427b0[4];
extern int DAT_00542960[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[160]; };
int igRotateMode_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00542960[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    u.vt = (int)&DAT_005427b0[0];
    return *(int *)&u.b[*(int *)((char *)DAT_00586dc8[0] + 916)];
}
