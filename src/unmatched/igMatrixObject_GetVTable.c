struct Obj { int *vt; char pad[76]; };
int igObject_InitHeader(struct Obj *);
int igMatrix44f_SetIdentity(char *);
extern int DAT_0052bc10[4];
extern void * DAT_00586dc8[4];
int igMatrixObject_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bc10[0];
    igMatrix44f_SetIdentity(obj.pad + 4);
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
