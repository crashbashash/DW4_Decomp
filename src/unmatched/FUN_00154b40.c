/* 0x00154b40 — FUN_00154b40. hand-matched (member access keeps the base pointer, finding #509's
 * shape); verified byte-identical to retail by tools/verify.py. */
int FUN_00154ad0();
typedef struct Obj { char pad[29]; unsigned char f29; } Obj;

int FUN_00154b40(Obj *arg0) {
    int temp_v0;
    if (arg0->f29 != 0) {
        temp_v0 = FUN_00154ad0();
        arg0->f29 = 0U;
        return temp_v0 & 0xFF;
    }
    return 1;
}
