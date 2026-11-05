int List_Reserve();
int List_Resize();
struct L { int p0; int p1; int n; int cap; };
struct O { char pad[16]; struct L *a; struct L *b; };
void FUN_0030cfa0(struct O *arg0) {
    struct L *temp_a0;
    struct L *temp_a0_2;
    struct L *temp_a0_3;
    struct L *temp_a0_4;
    temp_a0 = arg0->a;
    if (!(0 > temp_a0->cap)) {
        temp_a0->n = 0;
    } else {
        List_Resize(temp_a0, 0, 1);
    }
    temp_a0_2 = arg0->a;
    if (!(0 < temp_a0_2->n)) {
        List_Reserve(temp_a0_2, 0, 1);
    }
    temp_a0_3 = arg0->b;
    if (temp_a0_3 != 0) {
        if (!(0 > temp_a0_3->cap)) {
            temp_a0_3->n = 0;
        } else {
            List_Resize(temp_a0_3, 0, 4);
        }
        temp_a0_4 = arg0->b;
        if (!(0 < temp_a0_4->n)) {
            List_Reserve(temp_a0_4, 0, 4);
        }
    }
}
