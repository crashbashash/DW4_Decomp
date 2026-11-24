int FUN_001d9970(int *a, int *b) {
    float diff = ((SortListView *)DAT_005629f8[0])->_data[*b]->key - ((SortListView *)DAT_005629f8[0])->_data[*a]->key;
    if (diff > 0.0f) { return 1; }
    return -1;
}

int FUN_001d99d0(int *arg0, int *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)(DAT_005629f8[0]) + 16);
    return (int) (*(int *)((char *)((*(int *)(temp_a1 + (*arg0 * 4)))) + 20) - *(int *)((char *)((*(int *)(temp_a1 + (*arg1 * 4)))) + 20)) / 12;
}

int FUN_001d9a30(int *a, int *b) {
    int y = *b;
    int x = *a;
    SortItemView_1d9a30 **d = ((SortListView_1d9a30 *)DAT_005629f8[0])->_data;
    int n = (d[y]->pos - d[x]->pos) / 12;
    float diff;
    if (n == 0) { return n; }
    diff = d[x]->key - d[y]->key;
    return (diff > 0.0f) ? 1 : -1;
}

void FUN_001d9ac0(struct A_1d9ac0 *arg0, int arg1, int arg2) {
    R_1d9ac0 *p;
    L_1d9ac0 *l;
    int n1;
    int i;
    int n2;
    int j;

    ((Gap::Core::igObjectList *)arg0->b->list)->append((Gap::Core::igObject *)arg1);
    FUN_001db720((igSorter *)arg0, (igGeometry *)arg0->b, (igAttrStackManager *)arg2);
    l = arg0->b->list;
    n1 = l->cnt;
    for (i = 0; i < n1; i++) {
        p = l->arr[i];
        if (p) {
            p->refs -= 1;
            if (0 == ((unsigned long long)((long long)p->refs << 0x29) >> 0x29)) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    n2 = l->cnt;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->cnt = 0;
}

void FUN_001d9bb0(void *arg0, int arg1) {
    FUN_001b0250((PendingValueCollector *)arg1, (PendingIntList *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 12)));
}

