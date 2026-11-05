struct Obj { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" {
void *FUN_00198cc0(int);
int FUN_00199080();
int FUN_002d8310(...);
int FUN_003087a0(...);
int Memory_GetAllocatorBySelector(int);
int igNamedObject_SetName(...);
void igObject_Destroy(void *);
extern int DAT_004e4870[4];
extern int DAT_004fb3a8[4];
extern int DAT_00586dd0[4];
extern int DAT_00587038[4];
}
extern "C" void FUN_001d8ab0(void) {
    Obj *volatile a;
    Obj *b;
    Obj *t;
    FUN_00199080();
    a = (Obj *)FUN_00198cc0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    igNamedObject_SetName(a, &DAT_004e4870[0]);
    FUN_003087a0(&b, DAT_00586dd0[0], &DAT_004fb3a8[0]);
    FUN_002d8310((Obj *)(long)b, a);
    if (b != 0) {
        b->u.w = b->u.w - 1;
        if (b->u.b.cnt == 0) igObject_Destroy(b);
    }
    t = a;
    if (t != 0) {
        t->u.w = t->u.w - 1;
        if (t->u.b.cnt == 0) igObject_Destroy(t);
    }
}
