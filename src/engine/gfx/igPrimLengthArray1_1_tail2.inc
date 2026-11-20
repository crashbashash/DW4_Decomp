int Gap__Gfx__igPrimLengthArray1_1__vfunc_23(P_167240 *arg0, int arg1, int arg2) {
    int temp_s0;

    arg0->f10 = arg2;
    arg0->fc = arg1;
    temp_s0 = arg0->fc * 4;
    if (temp_s0 != 0) {
        arg0->f8 = (int)((Gap::Core::igObject *)arg0)->realloc((void *)arg0->f8, temp_s0);
    } else {
        if (arg0->f8 != 0) {
            ((Gap::Core::igObject *)arg0)->free((void *)arg0->f8);
        }
        arg0->f8 = 0;
    }
    return temp_s0;
}

/* Stores the length `length` of primitive strip `stripIndex` in the per-strip length table
 * (_lengthData is an int array, _numStrips entries). */

void Gap__Gfx__igPrimLengthArray1_1__vfunc_26(igPrimLengthArray1_1 *self, int stripIndex, int length) {
    *(int *)(self->_lengthData + (stripIndex * 4)) = length;
}

/* Returns the length of primitive strip `stripIndex` from the per-strip length table (_lengthData
 * is an int array, _numStrips entries); the getter paired with the setter in vfunc_26. */

int Gap__Gfx__igPrimLengthArray1_1__vfunc_27(igPrimLengthArray1_1 *self, int stripIndex) {
    return *(int *)(self->_lengthData + (stripIndex * 4));
}

int Gap__Gfx__igPrimLengthArray1_1__vfunc_24(igPrimLengthArray1_1 *arg0, int dummy1, int arg2) {
    return arg0->_lengthData + (arg2 * 4);
}

void Gap__Gfx__igPrimLengthArray1_1__vfunc_25(void) {

}

void *FUN_00167310(png_structp png, int size) {
    return ((Gap::Core::igObject *)DAT_00560840)->malloc(size);
}

void FUN_00167320(png_structp png, void *storage) {
    ((Gap::Core::igObject *)DAT_00560840)->free(storage);
}

void FUN_00167330(png_structp png, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(png_get_io_ptr(png));
    ((DW4VC_108_3 *)(temp_v0))->vX((int)(arg1), (int)(1), (int)(arg2));
}

void FUN_00167380(void) {

}

void FUN_00167390(void) {

}

