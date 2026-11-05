extern "C" {
int FUN_002e2d30(...);
int igObject_IsKindOf(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
extern int DAT_00585a60[4];
int FUN_002ea0d0(void **arg0, int arg1, int arg2);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
int FUN_002ea0d0(void **arg0, int arg1, int arg2) {
    int meta;
    int i;
    int w;
    struct F { char p[8]; int f8; int f12; } *f;
    meta = ((DW4VC_88_0 *)(arg0))->vX();
    for (i = 0; i < igMetaObject_GetFieldCount(meta); i++) {
        f = (F *)igMetaObject_GetFieldAt(meta, i);
        if (igObject_IsKindOf(f, DAT_00585a60[0]) != 0) {
          w = *(int *)((char *)arg0 + f->f8);
          if (w == arg2) {
            FUN_002e2d30(arg1, arg0, f->f12, arg2);
            return 1;
        }
        }
    }
    return 0;
}
