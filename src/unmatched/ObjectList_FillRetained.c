typedef struct { char pad[4]; int f4; } R;
typedef struct { char pad[8]; int cnt; char pad2[4]; R **data; } L;
int igObject_Destroy();
void ObjectList_FillRetained(L *arg0, R *arg1) {
    int n;
    int i;
    int j;
    int cnt;
    R **data;
    int k;
    R *t;
    n = arg0->cnt;
    if (arg1 != 0) {
        for (i = 0; i < n; i++) {
            arg1->f4 = arg1->f4 + 1;
        }
    }
    for (j = 0; j < n; j++) {
        t = arg0->data[j];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    cnt = arg0->cnt;
    data = arg0->data;
    for (k = 0; k < cnt; k++) {
        data[k] = arg1;
    }
}
