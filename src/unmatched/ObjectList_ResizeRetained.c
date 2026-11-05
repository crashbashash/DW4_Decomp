typedef struct { char pad[4]; int f4; } R;
typedef struct { char pad[8]; int cnt; int cap; R **data; } L;
int memset();
int List_Resize();
int igObject_Destroy();
void ObjectList_ResizeRetained(L *arg0, int arg1) {
    int n;
    int j;
    int k;
    R *t;
    n = arg0->cnt;
    if (arg1 <= n) {
        for (j = arg1; j < n; j++) {
            t = arg0->data[j];
            if (t != 0) {
                t->f4 = t->f4 - 1;
                if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        for (k = arg1; k < n; k++) {
            arg0->data[k] = 0;
        }
        arg0->cnt = arg1;
        return;
    }
    if (arg1 >= 0) {
        if (arg1 <= arg0->cap) {
            arg0->cnt = arg1;
        } else {
            List_Resize(arg0, arg1, 4);
        }
    }
    memset((char *)arg0->data + n * 4, 0, (arg1 - n) * 4);
}
