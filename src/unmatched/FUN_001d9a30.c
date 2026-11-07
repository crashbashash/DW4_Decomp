typedef struct SortItemView { char pad[20]; char *pos; float key; } SortItemView;
typedef struct SortListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SortItemView **_data; } SortListView;
extern SortListView *DAT_005629f8;
int FUN_001d9a30(int *a, int *b) {
    int y = *b;
    int x = *a;
    SortItemView **d = DAT_005629f8->_data;
    int n = (d[y]->pos - d[x]->pos) / 12;
    float diff;
    if (n == 0) { return n; }
    diff = d[x]->key - d[y]->key;
    return (diff > 0.0f) ? 1 : -1;
}
