/* Setter for the decal extension's `_context` field: stores the context object reference. */

void Gap__Gfx__igPsx2DecalExt__vfunc_29(igPsx2DecalExt *self, int context) {
    self->_context = context;
}

void Gap__Gfx__igPsx2DecalExt__vfunc_30(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
    FUN_0020d910((arg1 * *(int *)((char *)(arg0) + 28)));
}

