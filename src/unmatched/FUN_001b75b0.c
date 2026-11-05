int List_Resize();
struct L { int p0; int p1; int size; int cap; long long *data; };
void FUN_001b75b0(void *arg0, long long arg1) {
    int temp_s2;
    struct L *temp_s1;

    temp_s1 = *(struct L **)((char *)arg0 + 240);
    temp_s2 = temp_s1->size;
    if (temp_s2 < temp_s1->cap) {
        *(volatile int *)&temp_s1->size += 1;
    } else {
        List_Resize(temp_s1, temp_s2 + 1, 8);
    }
    temp_s1->data[temp_s2] = arg1;
}
