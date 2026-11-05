struct Rc { int vt; int refs; };
extern "C" {
int FUN_002d8310(...);
void *FUN_002d8eb0(...);
int igObject_IsKindOf(...);
int ObjectList_AppendUniqueRetained(...);
void *igMetaObject_CreateInstanceDefault(...);
void *igMetaObject_FindFieldByName(...);
int igObjectRefMetaField_Assign(...);
int igObjectSystem_FindMetaByNameDefault(...);
int igObject_Destroy(...);
extern int DAT_004f9a50[4];
extern int DAT_004fb3b0[4];
extern int DAT_004fb3b8[4];
extern int DAT_004fb3c8[4];
extern int DAT_004fb3d8[4];
extern int DAT_004fb3f0[4];
extern void *DAT_00585b20[4];
extern void *DAT_00585b60[4];
void FUN_00309fe0(int arg0);
}
struct V88 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
struct Fld { char pad[8]; int off; };
struct C1 {
    Fld *Cast(void *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_00585b20[0]) != 0) { return (Fld *)p; }
        return 0;
    }
    void *CastL(void *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_00585b60[0]) != 0) { return p; }
        return 0;
    }
};
void FUN_00309fe0(int arg0) {
    C1 c;
    int s0m, s1m;
    void *s1;
    Rc *sp5C;
    if (arg0 != 0) {
        s0m = igObjectSystem_FindMetaByNameDefault(&DAT_004fb3b0[0]);
        if (s0m != 0) {
            s1 = FUN_002d8eb0(arg0, &DAT_004f9a50[0]);
            if (s1 != 0 && igObject_IsKindOf(s1, s0m) != 0) {
                s1m = igObjectSystem_FindMetaByNameDefault(&DAT_004fb3b8[0]);
                if (s1m != 0) {
                    Rc *t;
                    Fld *f1, *f2, *f3;
                    void *l;
                    *(Rc * volatile *)&sp5C = (Rc *)igMetaObject_CreateInstanceDefault(s1m);
                    t = *(Rc * volatile *)&sp5C;
                    if (t) t->refs = t->refs + 1;
                    {
                        Rc *u = sp5C;
                        u->refs = u->refs - 1;
                        if (((unsigned long long)(long long)u->refs & 0x7fffffULL) == 0) igObject_Destroy(u);
                    }
                    f1 = c.Cast(igMetaObject_FindFieldByName(((V88 *)sp5C)->vX(), &DAT_004fb3c8[0]));
                    igObjectRefMetaField_Assign(f1, sp5C, s1);
                    f2 = c.Cast(igMetaObject_FindFieldByName(((V88 *)sp5C)->vX(), &DAT_004fb3d8[0]));
                    f3 = c.Cast(igMetaObject_FindFieldByName(((V88 *)sp5C)->vX(), &DAT_004fb3f0[0]));
                    l = c.CastL(*(void **)((char *)sp5C + f3->off));
                    if (l != 0) ObjectList_AppendUniqueRetained(l, s1);
                    igObjectRefMetaField_Assign(f2, sp5C, 0);
                    FUN_002d8310(arg0, sp5C);
                    {
                        Rc *u = sp5C;
                        if (u != 0) {
                            u->refs = u->refs - 1;
                            if (((unsigned long long)(long long)u->refs & 0x7fffffULL) == 0) igObject_Destroy(u);
                        }
                    }
                }
            }
        }
    }
}
