/* 0x001d31d0 - FUN_001d31d0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int List_Resize();
struct L1d { int a; int b; volatile int count; int cap; int *data; };
int FUN_001d31d0(void *arg0, int arg1) {
    struct L1d *temp_s1;
    temp_s1 = (struct L1d *)(*(int *)((char *)(arg0) + 16));
    if (temp_s1 != 0) {
        int temp_s2;
        temp_s2 = temp_s1->count;
        if (temp_s2 < temp_s1->cap) {
            temp_s1->count = temp_s1->count + 1;
        } else {
            List_Resize(temp_s1, temp_s2 + 1, 4);
        }
        temp_s1->data[temp_s2] = arg1;
    }
    return 1;
}
