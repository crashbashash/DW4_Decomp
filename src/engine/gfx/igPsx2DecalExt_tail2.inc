/* Setter for the decal extension's `_context` field: stores the context object reference. */

void Gap__Gfx__igPsx2DecalExt__vfunc_29(igPsx2DecalExt *self, int context) {
    self->_context = context;
}

void Gap__Gfx__igPsx2DecalExt__vfunc_30(int arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
    p2SetDepthBias((arg1 * *(int *)((char *)(arg0) + 28)));
}

