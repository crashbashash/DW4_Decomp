/* 0x00153c40 — igPsx2ImageConvert_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
struct Obj { int *vt; char pad[4]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_005255a0[4];
extern void * DAT_00586dc8[4];
int igPsx2ImageConvert_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005255a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
