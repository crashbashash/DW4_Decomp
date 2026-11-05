extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int ObjectList_AppendRetainedList(...);
}
struct List { char p[8]; int n; char q[4]; T **arr; };
struct Obj { char p[8]; List *list; };
extern "C" void FUN_001c5790(Obj *arg0, int arg1);
void FUN_001c5790(Obj *arg0, int arg1) {
    List *l = arg0->list;
    int n = l->n;
    int i;
    for (i = 0; i < n; i++) {
        T *old = l->arr[i];
        if (old) {
            --old->references;
            if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                igObject_Destroy(old);
        }
    }
    int n2 = l->n;
    int j;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->n = 0;
    ObjectList_AppendRetainedList(arg0->list, arg1);
}
