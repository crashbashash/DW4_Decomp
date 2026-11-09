int ChangeThreadPriority();
int GetThreadId();
int List_Resize();
struct Obj { int p0; int refs; };
struct List { int p0; int p4; int count; int cap; int *items; };
struct Mgr { int p0; int p4; struct List *list; };
void Gap__Core__igPsx2ThreadManager__vfunc_24(struct Mgr *arg0, struct Obj *arg1) {
    int prio; struct List *lst; int n; int id;
    arg1->refs = arg1->refs + 1;
    id = GetThreadId();
    prio = ChangeThreadPriority(id, 1);
    lst = arg0->list;
    n = (*(int const *)&lst->count);
    if (n < lst->cap) {
        lst->count = lst->count + 1;
    } else {
        List_Resize(lst, n + 1, 4);
    }
    lst->items[n] = (int)arg1;
    ChangeThreadPriority(id, prio);
}
