struct Obj { int *vt; char pad[76]; };
int igObject_InitHeader(struct Obj *);
int igMatrix44f_SetIdentity(void *);
extern int DAT_00523420[4];
extern void * DAT_00586dc8[4];
int igModelViewMatrixAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523420[0];
    igMatrix44f_SetIdentity(&obj.pad[8]);
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
