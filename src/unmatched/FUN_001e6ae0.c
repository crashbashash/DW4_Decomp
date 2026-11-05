/* 0x001e6ae0 - FUN_001e6ae0. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
int FUN_001906d0();
struct S1e { int a, b, cnt, d, base; };
void FUN_001e6ae0(struct S1e *arg0) {
    FUN_001906d0(arg0->base + (arg0->cnt - 1) * 64);
}
