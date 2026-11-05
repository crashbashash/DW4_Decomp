extern "C" {
typedef struct Obj { int w0; unsigned refs; } Obj;
int FUN_0037cc50(int *, int);
int FUN_003a6b50(int);
int List_RemoveWordAt(int *, int);
int igObject_Destroy(Obj *);
void FUN_0037d4a0(int *arg0);
}

void FUN_0037d4a0(int *arg0) {
    int *l;
    Obj *o;
    FUN_0037cc50(arg0, 3);
    if (*(int *)(arg0[10] + 8) > 0) {
        do {
            FUN_003a6b50(*(int *)(**(int **)(arg0[10] + 16) + 12));
            l = (int *)arg0[10];
            o = (Obj *)**(int **)(l + 4);
            if (o != 0) {
                --o->refs;
                if ((o->refs & 0x7fffff) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(l, 0);
            ((int *)l[4])[l[2]] = 0;
        } while (*(int *)(arg0[10] + 8) > 0);
    }
}
