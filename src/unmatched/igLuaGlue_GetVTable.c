struct Obj { int *vt; char pad[4]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_0052d540[4];
extern void * DAT_00586dc8[4];
int igLuaGlue_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d540[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
