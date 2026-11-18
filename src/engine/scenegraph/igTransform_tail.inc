void igTransform_userConstruct(igTransform *self, int flag) {
    igNode_userConstruct((void **)self, flag);  /* takes (self, flag) straight from a0/a1 */
    if (flag == 0) {
        ((DW4VC_112_2 *)(self))->vX((int)(2), (int)(1));
    }
}

int igTransform_IsTransformable(igTransform *arg0) {
    void **temp_a0;

    if (((DW4VC_92_0 *)(((char *)(arg0) + 0)))->vX() > 1) {
        return 0;
    }
    temp_a0 = (void **)(arg0->_transformInput);
    if (temp_a0 == 0) {
        return 1;
    }
    return ((DW4VC_116_0 *)(temp_a0))->vX();
}

