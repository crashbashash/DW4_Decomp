/* 0x0016e180 — FUN_0016e180. hand-matched: a struct member keeps the base pointer where m2c
 * CSE'd arg+N (finding #509's shape); verified byte-identical by tools/verify.py. */
typedef struct Obj { char pad[24]; int f24; } Obj;

void FUN_0016e180(Obj *arg0, int arg1) {
    if ((arg1 != 0) && (arg0->f24 == 0)) {
        arg0->f24 = arg1;
    }
}
