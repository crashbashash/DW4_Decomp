class TrackedEntry { public: int f0; virtual void Delete(int flags); };
struct TrackedEntryList { int vt; unsigned int _refCount; int count; int cap; TrackedEntry **data; };
extern "C" {
void igObject_Destroy(void *);
void FUN_002da850(void *self, TrackedEntryList *list);
}
static inline void clearSlot(TrackedEntryList *l, int i) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = 0;
    }
}
void FUN_002da850(void *self, TrackedEntryList *list) {
    int i = 0;
    goto first;
next:
    if (list->data[i] != 0) {
        list->data[i]->Delete(1);
    }
    clearSlot(list, i);
    i++;
test:
    if (i < list->count) {
        goto next;
    }
done:
    list->_refCount = (int)list->_refCount - 1;
    if (((unsigned long long)((long long)(int)list->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(list);
    }
    return;
first:
    if (0 < list->count) {
        goto test;
    }
    goto done;
}
