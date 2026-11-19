/* Setter for the decal extension's `_context` field: stores the context object reference. */

void Gap__Gfx__igPsx2DecalExt__vfunc_29(igPsx2DecalExt *self, int context) {
    self->_context = context;
}

void Gap__Gfx__igPsx2DecalExt__vfunc_30(igPsx2DecalExt *self, int arg1) {
    self->_decalOffset = arg1;
    p2SetDepthBias((arg1 * self->_offsetUnits));
}

