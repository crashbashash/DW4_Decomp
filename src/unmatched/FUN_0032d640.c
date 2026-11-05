/* 0x0032d640 — FUN_0032d640. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int FUN_0010e0d8();
int FUN_00300db0();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct B { char pad[36]; int f36; };
struct A { char pad[8]; struct B *f8; int f12; };
void FUN_0032d640(int *arg0, struct A *arg1, int arg2) {
    while (1) {
        if (FUN_0010e0d8(arg1->f8, arg2, 0) < 0) {
            *arg0 = DAT_004fb418[0];
            return;
        }
        if (arg1->f8->f36 != 0) {
            arg1->f12 = FUN_00300db0(arg1, 0x20, 0x10);
            *arg0 = DAT_004fb410[0];
            return;
        }
    }
}
