class R { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); int rc; int f8; int f12; int f16; int f20; };
struct Lst { char pad[8]; int n; };
extern "C" {
void *FUN_002c77e0(...);
int FUN_002d7d60(...);
int FUN_002d86b0(...);
int List_InsertWords(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586730[4];
int FUN_002d8d00(Lst *list, int key, int name, int val);
}
int FUN_002d8d00(Lst *list, int key, int name, int val) {
    R * volatile sp6C;
    R * sp68;
    R *t;
    int idx, cnt, r;
    if (key == 0) {
        return -1;
    }
    idx = FUN_002d86b0(list, DAT_00586730[0], key);
    cnt = list->n;
    if (cnt > 0) {
        if (idx < cnt) {
            int f = FUN_002d7d60(list, idx);
            if (f == key) return -1;
        }
    }
    sp6C = (R *)FUN_002c77e0(igObject_GetAllocator(list));
    igNamedObject_SetName(sp6C, name);
    sp6C->f16 = val;
    sp6C->f20 = 2;
    sp6C->vX(key);
    sp6C->f12 = idx;
    sp68 = sp6C;
    t = sp68;
    if (t != 0) {
        t->rc = t->rc + 1;
    }
    List_InsertWords(list, idx, 1, &sp68);
    t = sp6C;
    r = t->f12;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    return r;
}
