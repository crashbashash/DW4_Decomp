/* 0x001c0e70 — FUN_001c0e70. hand-matched (member access keeps the base pointer, finding #509's
 * shape); verified byte-identical to retail by tools/verify.py. */
int FUN_002808f0();
typedef struct Obj { char pad[32]; int f32; } Obj;

void FUN_001c0e70(Obj *arg0) {
    arg0->f32 = FUN_002808f0(arg0->f32);
}
