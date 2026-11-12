void Gap__Core__igNamedObjectInfo__vfunc_23(This *arg0, int arg1, Obj_2fed50 *arg2) {
    Arr_2fed50 *a;
    int i = 0;
    /* matching construct: cxx_sweep — arg0->a assigned in the loop test */
    while (i < (a = arg0->a)->n) {
        Obj_2fed50 *o = (Obj_2fed50 *)a->d[i];
        if (o == arg2) {
            int *nm = o->name ? o->name : emptyString;
 FUN_002e2d30(arg1, arg0, nm, arg2, i, arg0);
            return;
        }
        i++;
    }
    FUN_002ea0d0((void **)arg0, arg1, (int)arg2, (int)arg2, i);
}

int FUN_002feeb0(struct L_2feeb0 *arg0, struct K *arg1, int arg2) {
    int i;
    int v;
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < arg0->n; i++) {
        v = arg0->items[i];
        if (v != 0 && arg2 == *(int *)(v + arg1->off)) {
            return v;
        }
    }
    return 0;
}

