// 0x00330630 - 180 bytes. Raise the thread priority, remove a value from the manager's list, restore.
extern "C" {
int ChangeThreadPriority(int, int);
int GetThreadId();
int List_RemoveWordAt(void *, int, int, int);
void Gap__Core__igPsx2ThreadManager__vfunc_25(void *arg0, int arg1);
}
struct L {
    char p[8]; int n; char q[4]; int *d;
    int FindIdx(int key) {
        int i;
        for (i = 0; i < n; i++) {
            if (key == d[i]) return i;
        }
        return -1;
    }
};
void Gap__Core__igPsx2ThreadManager__vfunc_25(void *arg0, int arg1) {
    volatile int sp4C;
    int tid = GetThreadId();
    int old = ChangeThreadPriority(tid, 1);
    L *list;
    int i;
    int key;
    sp4C = arg1;
    list = *(L **)((char *)arg0 + 8);
    key = sp4C;
    i = list->FindIdx(key);
    if (i >= 0) {
        List_RemoveWordAt(list, i, key, list->n);
    }
    ChangeThreadPriority(tid, old);
}
