int Gap__Sg__igTransform__vfunc_28(void)
{
    return 2;
}

void Gap__Sg__igTransform__vfunc_29(igTransform *self) {
    void **transformInput;

    transformInput = (void **)(self->_transformInput);
    if (transformInput != 0) {
        ((DW4VC_132_0 *)(transformInput))->vX();
        igMatrix44f_SetIdentity(&self->_m[0]);
    }
}

