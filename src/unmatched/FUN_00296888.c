/* Thin wrapper: forwards the sub-object stored at +68 of its argument (hypothesis: a CRI Sofdec/ADX handle). */
typedef struct Obj { char pad[68]; void *sub; } Obj;
extern void FUN_0029b0b0(void *);
void FUN_00296888(Obj *o) { FUN_0029b0b0(o->sub); }
