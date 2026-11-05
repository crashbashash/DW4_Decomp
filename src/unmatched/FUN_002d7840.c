/* 0x002d7840 — FUN_002d7840. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int FUN_002d7130();
int FUN_002d7280();
int List_RemoveAt();
struct L { char pad[8]; int cnt; int cap; int *data; };
struct S { char pad[12]; struct L *f12; char pad2[8]; unsigned char f24; };

void FUN_002d7840(struct S *arg0, int arg1) {
    int var_s0;
    struct L *temp_a0;
    int *temp_v1;
    int a, b;

    for (var_s0 = arg0->f12->cnt - 1; var_s0 >= 0; var_s0--) {
        temp_a0 = arg0->f12;
        temp_v1 = temp_a0->data + var_s0 * 2;
        b = temp_v1[1];
        a = temp_v1[0];
        if ((a == arg1) || (b == arg1)) {
            List_RemoveAt(temp_a0, var_s0, 8);
        }
    }
    if (arg0->f24 != 0) {
        FUN_002d7280(arg0);
        FUN_002d7130(arg0);
    }
}
