/* Getter: the rotation (quaternion) keyframe list (`_quatList`). */

int FUN_001bf3d0(igTransformSequence1_5 *self) {
    return self->_quatList;
}

/* Getter: the translation keyframe list (`_xlateList`). */

int Gap__Sg__igTransformSequence1_5__vfunc_43(igTransformSequence1_5 *self) {
    return self->_xlateList;
}

/* Number of keyframe times: the element count of the long-time list (`_timeListLong` is an
 * igLongList; `_count` is at +8). */

int Gap__Sg__igTransformSequence1_5__vfunc_39(igTransformSequence1_5 *self) {
    return ((igLongList *)self->_timeListLong)->_count;
}

void FUN_001bf400(int arg0, int arg1, long long arg2) {
    unsigned short *p;
    int idx;
    int base;
    arg0 = *(int *)(arg0 + 16);
    idx = arg1 << 1;
    base = *(int *)(arg0 + 16);
    base = base + idx;
    p = (unsigned short *)base;
    *p = 0;
    if (arg2 < 0) {
        arg2 = -arg2;
        *p |= 0x8000;
    }
    *p |= (arg2 >> 0x17) & 0xFFFF;
}

