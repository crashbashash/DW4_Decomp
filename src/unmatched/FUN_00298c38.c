/* Thin wrapper: forwards the handle stored at +172 of its argument to FUN_002b3e80 (one of four sibling accessors at 0x298bf0..0x298c38). */
extern void FUN_002b3e80(void *);
typedef struct Obj { char pad[172]; void *sub; } Obj;
void FUN_00298c38(Obj *o) { FUN_002b3e80(o->sub); }
