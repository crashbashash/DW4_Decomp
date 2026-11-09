typedef struct SorterPackageView { char pad[20]; unsigned int key; } SorterPackageView;
typedef struct SorterPackageListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SorterPackageView **_data; } SorterPackageListView;
typedef struct SorterIndexListView { int _vtable; unsigned int _refCount; int _count; int _capacity; int *_data; } SorterIndexListView;
typedef struct SorterOpaqueView { char pad[60]; SorterIndexListView *_opaquePackageIndices; } SorterOpaqueView;
extern SorterPackageListView *DAT_005629f8;
void FUN_001da790(SorterOpaqueView *o) {
    int c;
    unsigned int prev;
    int start;
    unsigned int key;
    int j;
    int i;
    int *p;
    int n;
    SorterIndexListView *l;
    n = o->_opaquePackageIndices->_count;
    start = 1;
    if (n < 2) { return; }
    while (start > 0) {
        j = start - 1;
        prev = DAT_005629f8->_data[o->_opaquePackageIndices->_data[j]]->key;
        i = start;
        start = 0;
        for (; i < n; i++) {
            l = o->_opaquePackageIndices;
            p = &l->_data[i];
            key = DAT_005629f8->_data[*p]->key;
            if (key < prev) {
                c = l->_count;
                if (c != 0 && i >= 0 && c > i) {
                    j = i - 1;
                    if (j >= 0 && c > j) {
                        int t = *(const int *)p;
                        *p = p[-1];
                        p[-1] = t;
                    }
                }
                prev = key;
                if (start == 0) {
                    start = (i > 1) ? i - 1 : 1;
                }
            }
            prev = key;
        }
    }
}
