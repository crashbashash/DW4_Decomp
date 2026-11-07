typedef struct List { int pad[2]; int count; int capacity; } List;
void List_Reserve(List *l, int count, int size);
void Gap__Core__igStringRefList__vfunc_18(List *l) {
    int n = l->count;
    if (n < l->capacity) {
        List_Reserve(l, n, 4);
    }
}
