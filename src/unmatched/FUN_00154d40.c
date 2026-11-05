/* 0x00154d40 — FUN_00154d40. hand-matched (member access keeps the base pointer, finding #509's
 * shape); verified byte-identical to retail by tools/verify.py. */
int FUN_00154d90();
typedef struct Obj { char pad[29]; unsigned char f29; } Obj;

int FUN_00154d40(Obj *arg0) {
    int temp_v0;
    if (arg0->f29 == 0) {
        temp_v0 = FUN_00154d90() & 0xFF;
        arg0->f29 = 1U;
        return temp_v0;
    }
    return 1;
}
