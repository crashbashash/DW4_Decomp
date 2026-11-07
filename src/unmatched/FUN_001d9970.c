typedef struct SortItemView { char pad[24]; float key; } SortItemView;
typedef struct SortListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SortItemView **_data; } SortListView;
extern SortListView *DAT_005629f8;
int FUN_001d9970(int *a, int *b) {
    float diff = DAT_005629f8->_data[*b]->key - DAT_005629f8->_data[*a]->key;
    if (diff > 0.0f) { return 1; }
    return -1;
}
