extern void FUN_002b3e70(void *);
typedef struct Obj { char pad[172]; void *sub; } Obj;
void FUN_00298c08(Obj *o) { FUN_002b3e70(o->sub); }
