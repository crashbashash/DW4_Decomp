typedef struct IntList { int _vtable; int _refCount; int _count; int _capacity; int *_data; } IntList;
int FUN_001ee270();
int List_Resize();
extern int DAT_0048a4f0[4];
static inline int count_of(const IntList *list) { return list->_count; }
void FUN_0016cc60(char *arg0) {
    int idx;
    IntList *list;
    int top;
    int value;
    idx = *(int *)(arg0 + 964);
    if (idx >= 0) {
        list = **(IntList ***)(*(int *)(*(int *)(arg0 + 960) + 16) + idx * 4);
        value = FUN_001ee270(*(int *)((char *)DAT_0048a4f0 + *(int *)(arg0 + 1400) * 4));
        top = count_of(list);
        if (top < list->_capacity) {
            list->_count = list->_count + 1;
        } else {
            List_Resize(list, top + 1, 4);
        }
        list->_data[top] = value;
    }
}
