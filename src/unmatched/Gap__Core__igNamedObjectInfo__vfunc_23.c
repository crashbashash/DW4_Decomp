/* Name-or-default via ?: (not an empty-then if); default compiler */
typedef struct Arr { int p0; int p1; int n; int p3; int **d; } Arr;
typedef struct Obj { int p0; int p1; int *name; } Obj;
typedef struct This { char pad[20]; Arr *a; } This;
extern int DAT_004e0858[4];
void FUN_002e2d30(int, This *, int *, Obj *, int, This *);
void FUN_002ea0d0(This *, int, Obj *, Obj *, int);
void Gap__Core__igNamedObjectInfo__vfunc_23(This *arg0, int arg1, Obj *arg2) {
    Arr *a = arg0->a;
    int i = 0;
    while (i < a->n) {
        Obj *o = (Obj *)a->d[i];
        if (o == arg2) {
            int *nm = o->name ? o->name : DAT_004e0858;
 FUN_002e2d30(arg1, arg0, nm, arg2, i, arg0);
            return;
        }
        i++;
    }
    FUN_002ea0d0(arg0, arg1, arg2, arg2, i);
}
