typedef igSmartPointer<igTDataList<igNamedObject *> > igNamedObjectListRef;

/* Writes the directory entry for `object`: under its own name when the info lists it, else through
 * the base class, which looks for the object among the info's reference fields. */
void Gap__Core__igNamedObjectInfo__vfunc_23(igNamedObjectInfo *self, int file, igNamedObject *object) {
    for (int i = 0; i < ((igNamedObjectListRef &)self->_objects)->count(); i++) {
        igNamedObject *named = ((igNamedObjectListRef &)self->_objects)->get(i);
        if (named == object) {
            FUN_002e2d30(file, self, named->_name ? (int *)named->_name : emptyString, object);
            return;
        }
    }
    FUN_002ea0d0((void **)self, file, (int)object);
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

