int Gap__Sg__igGroup__vfunc_26(void *arg0) {
    Obj_1c6260 *self = (Obj_1c6260 *)arg0;
    unsigned int n;
    unsigned int i;
    if (self->vX() > 1) {
        return 0;
    }
    n = 0;
    if (self->list != 0) {
        n = self->list->count;
    }
    for (i = 0; i < n; i++) {
        if (self->list->data[i]->vX() == 0) {
            return 0;
        }
    }
    return 1;
}

