int List_Resize();
struct L1d { int a; int b; int count; int cap; int *data; };
static inline int count_of(const struct L1d *list) { return list->count; }
int FUN_001d31d0(void *arg0, int arg1) {
        int temp_s2;
    struct L1d *temp_s1;
    temp_s1 = (struct L1d *)(*(int *)((char *)(arg0) + 16));
    if (temp_s1 != 0) {
        temp_s2 = temp_s1->count;
        if (temp_s2 < temp_s1->cap) {
            temp_s1->count = 1 + count_of(temp_s1);
        } else {
            List_Resize(temp_s1, temp_s2 + 1, 4);
        }
        temp_s1->data[temp_s2] = arg1;
    }
    return 1;
}
