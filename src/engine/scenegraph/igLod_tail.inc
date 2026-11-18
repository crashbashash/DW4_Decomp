void igLod_Reset(igLod *self) {
    igObject *lastRange;
    lastRange = (igObject *)(self->_lastRange);
    if (lastRange != 0) {
        lastRange->_refCount = lastRange->_refCount - 1;
        if (((unsigned long long) ((long long)(int) lastRange->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)lastRange);
        }
    }
    self->_lastRange = 0;
    self->_lastIndex = -1;
    self->_lastLower = 0;
    self->_lastUpper = 0;
}

void igLod_UserPostLoad(void **arg0) {
    igGroup_UserPostLoad((SgLinkNode *)arg0);
    ((DW4VC_124_0 *)(arg0))->vX();
}

void igLod_Transform(igLod *self, float *matrix) {
    igGroup_Transform((int *)self, (int)(matrix));
    Vec3f_TransformProjective(self->_center, self->_center, matrix);
}

