void igLod_Reset(igLod *self) {
    igObject *lastRange;
    lastRange = (igObject *)(self->_lastRange);
    igObject::release(lastRange);
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
    Vec3f_TransformProjective(self->_center.vec, self->_center.vec, matrix);
}

