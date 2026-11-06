typedef struct Obj { int vt; int refs; } Obj;
typedef struct Self { char pad[44]; Obj *r44; Obj *r48; } Self;
int FUN_001c6520(Self *, int);
int FUN_001cb340(Self *, int, int);
void Gap__Core__igShaderFactory__vfunc_23(Self *, int, Obj *, int);
void igObject_Destroy(Obj *);
Obj *igObject_GetAllocator(int);
#define REL(p) { Obj *o = (p); if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy(o);}}
#define ADD(o) if(o){ ++(o)->refs; }
int Gap__Core__igIniShaderFactory__vfunc_23(Self *self, int a1, Obj *a2, int a3) {
    unsigned char ok = 1;
    if (FUN_001c6520(self, 1) != 0) {
        Obj *n;
        ADD(a2);
        REL(self->r48);
        self->r48 = a2;
        n = igObject_GetAllocator(a1);
        ADD(n);
        REL(self->r44);
        self->r44 = n;
        ok = !FUN_001cb340(self, a1, a3);
    }
    if (ok) Gap__Core__igShaderFactory__vfunc_23(self, a1, a2, a3);
    REL(self->r48);
    self->r48 = 0;
    REL(self->r44);
    self->r44 = 0;
    return !ok;
}
