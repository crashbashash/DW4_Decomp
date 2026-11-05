typedef struct Obj { int pad; int refs; } Obj;
extern int FUN_002d8370(Obj *, unsigned int);
extern unsigned int FUN_002d9120(Obj *);
extern int igObject_IsKindOf(int, Obj *);
extern int FUN_003087a0(Obj **, int, int);
extern Obj *igObjectSystem_FindMetaByNameDefault(int);
extern int igObject_Destroy(Obj *);
#define REL(p) if ((p) != 0) { (p)->refs = (p)->refs - 1; if (((unsigned long long)((long long)(p)->refs << 0x29) >> 0x29) == 0) { igObject_Destroy(p); } }

int FUN_00309a60(int arg0, int arg1, int arg2, int arg3) {
    Obj *b;
    Obj *volatile a;
    Obj *t;
    int s2;
    unsigned int i;
    int r;

    FUN_003087a0(&b, arg0, arg1);
    a = igObjectSystem_FindMetaByNameDefault(arg2);
    t = a;
    if (t != 0) {
        t->refs = t->refs + 1;
    }
    if (b == 0 || (s2 = 0, a == 0)) {
        t = a;
        REL(t)
        t = b;
        REL(t)
        return 0;
    }
    for (i = 0; i < FUN_002d9120(b); i++) {
        if (igObject_IsKindOf(FUN_002d8370(b, i), a) != 0) {
            if (s2++ == arg3) {
                r = FUN_002d8370(b, i);
                t = a;
                REL(t)
                t = b;
        REL(t)
                return r;
            }
        }
    }
    t = a;
    REL(t)
    t = b;
    REL(t)
    return 0;
}
