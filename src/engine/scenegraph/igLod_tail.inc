void Gap__Sg__igLod__vfunc_31(igLod *self) {
    igObject *lastRange;
    lastRange = (igObject *)(self->_lastRange);
    if (lastRange != 0) {
        lastRange->_refCount = lastRange->_refCount - 1;
        if (((unsigned long long) ((long long)(int) lastRange->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)lastRange);
        }
    }
    self->_lastRange = 0;
    self->_lastIndex = -1;
    self->_lastLower = 0;
    self->_lastUpper = 0;
}

void Gap__Sg__igLod__vfunc_17(void **arg0) {
    FUN_001c5b80((SgLinkNode *)arg0);
    ((DW4VC_124_0 *)(arg0))->vX();
}

void Gap__Sg__igLod__vfunc_27(igLod *self, float *matrix) {
    FUN_001c6340((int *)self, (int)(matrix));
    Vec3f_TransformProjective(self->_center, self->_center, matrix);
}

