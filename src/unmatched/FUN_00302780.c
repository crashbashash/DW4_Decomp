/* 0x00302780 — FUN_00302780. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int igObject_Destroy();
struct R { int w0; int rc; };
struct A { char pad[8]; int f8; char pad2[48]; unsigned char f60; };
void FUN_00302780(struct A *arg0, int arg1, int arg2, struct R *arg3) {
    int temp_s0;
    struct R *temp_a0;

    temp_s0 = arg2 * 4;
    temp_a0 = ((struct R **)(arg1 + arg0->f8))[arg2];
    if (arg0->f60 != 0) {
        if (arg3 != 0) {
            arg3->rc = arg3->rc + 1;
        }
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    ((struct R **)(arg1 + arg0->f8))[arg2] = arg3;
}
