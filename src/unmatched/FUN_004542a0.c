/* 0x004542a0 — FUN_004542a0. hand-matched: a struct member keeps the base pointer where m2c
 * CSE'd arg+N (finding #509's shape); verified byte-identical by tools/verify.py. */
int FUN_002d7750();
typedef struct Obj { char pad[12]; int f12; } Obj;

void FUN_004542a0(Obj *arg0, int arg1) {
    int sp1C;
    FUN_002d7750(&sp1C, arg0->f12, arg1);
}
