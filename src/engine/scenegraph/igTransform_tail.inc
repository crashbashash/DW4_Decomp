void Gap__Sg__igTransform__vfunc_7(igTransform *self, int flag) {
    Gap__Sg__igNode__vfunc_09((void **)self, flag);  /* takes (self, flag) straight from a0/a1 */
    if (flag == 0) {
        ((DW4VC_112_2 *)(self))->vX((int)(2), (int)(1));
    }
}

int Gap__Sg__igTransform__vfunc_24(igTransform *arg0) {
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

