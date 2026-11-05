/* 0x002d3950 — FUN_002d3950. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int List_Reserve();
int List_Resize();
struct L { char pad[8]; int cnt; int cap; };
struct S { char pad[16]; struct L *f16; struct L *f20; };
void FUN_002d3950(struct S *arg0) {
    struct L *temp_a0;
    struct L *temp_a0_2;
    struct L *temp_a0_3;
    struct L *temp_a0_4;
    struct L *temp_a0_5;
    temp_a0 = arg0->f16;
    if (!(0 > temp_a0->cap)) {
        temp_a0->cnt = 0;
    } else {
        List_Resize(temp_a0, 0, 4);
    }
    temp_a0_2 = arg0->f16;
    if (!(0 < temp_a0_2->cnt)) {
        List_Reserve(temp_a0_2, 0, 4);
    }
    temp_a0_3 = arg0->f20;
    if (!(0 > temp_a0_3->cap)) {
        temp_a0_3->cnt = 0;
    } else {
        List_Resize(temp_a0_3, 0, 4);
    }
    temp_a0_4 = arg0->f20;
    if (temp_a0_4 != 0) {
    if (!(0 > temp_a0_4->cap)) {
        temp_a0_4->cnt = 0;
    } else {
        List_Resize(temp_a0_4, 0, 4);
    }
    temp_a0_5 = arg0->f20;
    if (!(0 < temp_a0_5->cnt)) {
        List_Reserve(temp_a0_5, 0, 4);
    }
    }
}
