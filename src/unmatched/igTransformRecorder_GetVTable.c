struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char sub1[64]; char sub2[64]; };
int igObject_InitHeader(struct Obj *); int igMatrix44f_SetIdentity(void *); int FUN_00195a90(struct Obj *, int);
extern int DAT_0052b7d0[4]; extern void * DAT_00586dc8[4];
int igTransformRecorder_GetVTable(void) { struct Obj o; int *p = (int *)&o; int t;
 igObject_InitHeader((struct Obj *)p); o.vt = &DAT_0052b7d0[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0;
 igMatrix44f_SetIdentity(o.sub1); igMatrix44f_SetIdentity(p + 24);
 t = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
 o.vt = &DAT_0052b7d0[0]; FUN_00195a90((struct Obj *)p, 0); return t; }