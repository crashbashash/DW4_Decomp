void Gap__Attrs__igLightStateAttr__vfunc_24(S_13ef30 *arg0, int arg1) {
    if (arg0->f16 != 0) {
        if (arg0->f16->f16 == -1) {
            arg0->f16->vX();
        }
        Gap__Gfx__igPsx2VisualContext__vfunc_79(arg1, arg0->f16->f16, arg0->f20);
    }
}

void Gap__Attrs__igLightStateAttr__vfunc_26(igLightStateAttr *arg0, void **arg1) {
    void *temp_v1;

    temp_v1 = (void *)(arg0->_light);
    if (temp_v1 != 0) {
        ((DW4VC_128_1 *)(((char *)(arg0) + 0)))->vX((int)(((DW4VC_320_1 *)(arg1))->vX((int)(*(int *)((char *)(temp_v1) + 16)))));
    }
}

/* Setter for the attribute's reflected _enabled flag. */
void Gap__Attrs__igLightStateAttr__vfunc_32(igLightStateAttr *self, char enabled) {
    self->_enabled = enabled;
}

void Gap__Attrs__igLightStateAttr__vfunc_29(igLightStateAttr *self) {
    void **light;

    light = (void **)(self->_light);
    if (light != 0) {
        ((BoundLightVtable *)(light))->vX();
    }
}

