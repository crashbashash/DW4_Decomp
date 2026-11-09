int List_Resize();
struct L { char pad[8]; int n; int cap; int *arr; };
struct A { char pad[8]; char f8; char pad2[15]; struct L *f24; struct L *f28; };
struct B { char pad[32]; unsigned char f32; char pad2[7]; unsigned char f40; };
static inline int n_of(const struct L *list) { return list->n; }
void FUN_001b1490(struct A *arg0, struct B *arg1, int arg2) {
    int c1;
    int c2;
    struct L *l1;
    struct L *l2;

    if (arg1->f32 == 0) {
        l1 = arg0->f24;
        c1 = l1->n;
        if (c1 < l1->cap) {
            l1->n = n_of(l1) + 1;
        } else {
            List_Resize(l1, c1 + 1, 4);
        }
        l1->arr[c1] = arg2;
        arg1->f32 = 1U;
    }
    if (arg1->f40 == 0) {
        l2 = arg0->f28;
        c2 = l2->n;
        if (c2 < l2->cap) {
            l2->n = n_of(l2) + 1;
        } else {
            List_Resize(l2, c2 + 1, 4);
        }
        l2->arr[c2] = arg2;
        arg1->f40 = 1U;
    }
    arg0->f8 = 1;
}
