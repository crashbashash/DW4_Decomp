void Gap__Sg__igTransformSequence1_5__vfunc_68(S0 *arg0) {
    S_temp_a0_1ab990 *temp_a0;

    arg0->f48 &= 0xF7;
    temp_a0 = arg0->f10;
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg0->f10 = 0;
}

/* Address of key {index} in this sequence's scale track, or 0 when the sequence does not drive
 * that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation slots, 8
 * = scale); the key array starts 16 bytes into the list object and each key is 0xC bytes. */

int Gap__Sg__igTransformSequence1_5__vfunc_50(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 8) {
        return *(int *)((char *)(self->_scaleList) + 16) + (index * 0xC);
    }
    return 0;
}

void Gap__Sg__igTransformSequence1_5__vfunc_67(S_1aba30 *arg0) {
    R_1aba30 *temp_a0;

    arg0->flags = arg0->flags & 0xFE;
    temp_a0 = arg0->ref;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if ((temp_a0->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg0->ref = 0;
}

long long Gap__Sg__igTransformSequence1_5__vfunc_65(void *arg0) {
    return *(long long *)((char *)arg0 + 88);
}

long long Gap__Sg__igTransformSequence1_5__vfunc_56(igTransformSequence1_5 *arg0, int arg1) {
    return *(long long *)(*(int *)((char *)(arg0->_timeListLong) + 16) + (arg1 * 8));
}

/* Address of key {index} in this sequence's translation track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0xC bytes. */

int Gap__Sg__igTransformSequence1_5__vfunc_42(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 1) {
        return *(int *)((char *)(self->_xlateList) + 16) + (index * 0xC);
    }
    return 0;
}

int Gap__Sg__igTransformSequence1_5__vfunc_41(igTransformSequence1_5 *arg0) { if (arg0->_drivenChannels & 1) return *(int *)((char *)(arg0->_xlateList) + 8); return 0; }

int Gap__Sg__igTransformSequence1_5__vfunc_69(void *arg0) {
    return (*(unsigned char *)((char *)(arg0) + 72) & 8) ? *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 8) : 0;
}

/* IgTransformSequence1_5 slot 60, returns the reflected _drivenChannels byte (+72). */

unsigned char Gap__Sg__igTransformSequence1_5__vfunc_60(igTransformSequence1_5 *self) {
    return self->_drivenChannels;
}

int FUN_001abb50(S_1abb50 *arg0, A *arg1) {
    int n;
    Rc_1abb50 *r;
    n = arg1->vX();
    if (n == 0 || (arg0->f8 != 0) != 0) {
        return 0;
    }
    if (arg1 != 0) {
        arg1->f4 = arg1->f4 + 1;
    }
    r = arg0->f8;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)r->refs & 0x7fffffULL) == 0) {
            igObject_Destroy((void *)r);
        }
    }
    arg0->f8 = (Rc_1abb50 *)arg1;
    arg0->f12 = igObject_AllocateStorage(arg0, n * 4);
    return 1;
}

