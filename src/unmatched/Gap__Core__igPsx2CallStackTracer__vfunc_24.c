int List_Resize();
extern int DAT_004c2618[4];
struct S { char pad[8]; int n; int cap; int *data; };
int Gap__Core__igPsx2CallStackTracer__vfunc_24(struct S *arg0) {
    int temp_s1;

    temp_s1 = (*(int const *)&arg0->n);
    if (temp_s1 < arg0->cap) {
        arg0->n = arg0->n + 1;
    } else {
        List_Resize(arg0, temp_s1 + 1, 4);
    }
    *(int *)((char *)arg0->data + (temp_s1 * 4)) = DAT_004c2618[0];
    return (int)arg0->data;
}
