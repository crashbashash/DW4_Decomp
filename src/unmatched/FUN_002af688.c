/* 0x002af688 — FUN_002af688 (52 bytes). Null-safe wrapper: returns FUN_002af6c0(arg0, p->f20, p->f24), or 0 when p is null. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002af6c0();

struct Pair14 {
    char pad[20];
    int f20;
    int f24;
};

int FUN_002af688(int arg0, struct Pair14 *p) {
    if (p == 0) {
        return 0;
    }
    return FUN_002af6c0(arg0, p->f20, p->f24);
}
