struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; char sub1[64]; char sub2[64]; char pad[4]; };
int igObject_InitHeader(struct Obj *); int igMatrix44f_SetIdentity(void *); int FUN_0019c0e0(struct Obj *, int); int ObjectRef_Destruct_00150eb0(void *, int);
extern int DAT_0052a400[4]; extern void * DAT_00586dc8[4];
int igBlendMatrixSelect_GetVTable(void) { struct Obj o; int *p = (int *)&o; int *q; int t;
 igObject_InitHeader((struct Obj *)p); o.vt = &DAT_0052a400[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0; o.f32 = 0; q = &o.f40; *q = 0;
 igMatrix44f_SetIdentity(o.sub1); igMatrix44f_SetIdentity(p + 27);
 t = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
 o.vt = &DAT_0052a400[0]; ObjectRef_Destruct_00150eb0(q, -1); p = (int*)&o; FUN_0019c0e0((struct Obj *)p, 0); return t; }
