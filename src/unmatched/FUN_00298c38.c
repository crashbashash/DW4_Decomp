extern void FUN_002b3e80(void *);
typedef struct Obj { char pad[172]; void *sub; } Obj;
void FUN_00298c38(Obj *o) { FUN_002b3e80(o->sub); }
