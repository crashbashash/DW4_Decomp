int igTransform_GetInherantFlags(void)
{
    return 2;
}

void igTransform_Reset(igTransform *self) {
    void **transformInput;

    transformInput = (void **)(self->_transformInput);
    if (transformInput != 0) {
        ((DW4VC_132_0 *)(transformInput))->vX();
        igMatrix44f_SetIdentity(&self->_m[0]);
    }
}

