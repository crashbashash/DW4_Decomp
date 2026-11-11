int Gap__Bec__ParticleArray__vfunc_22(ParticleArray *arg0, int arg1) {
    ((DW4VC_100_1 *)arg0)->vX(arg1, arg0->_arrayIndex);
    return arg0->_arrayIndex - 1;
}

void Gap__Bec__ParticleArray__vfunc_23(ParticleArray *arg0, char *arg1, unsigned int arg2) {
    char *s1;
    s1 = (char *)arg0->_particleArray + arg2 * (int)arg0->_particleDataSize /* matching construct: signed stride keeps the retail load order */;
    FUN_0015b820(s1, arg1);
    FUN_0015b820(s1 + 0xC, arg1 + 0xC);
    FUN_0015b820(s1 + 0x18, arg1 + 0x18);
    FUN_0015b7f0(s1 + 0x24, arg1 + 0x24);
    FUN_0015b7f0(s1 + 0x34, arg1 + 0x34);
    FUN_0015b7f0(s1 + 0x44, arg1 + 0x44);
    FUN_0015b7d0(s1 + 0x54, arg1 + 0x54);
    FUN_0015b7d0(s1 + 0x5C, arg1 + 0x5C);
    FUN_0015b7d0(s1 + 0x64, arg1 + 0x64);
    FUN_0015b7d0(s1 + 0x6C, arg1 + 0x6C);
    FUN_0015b7d0(s1 + 0x74, arg1 + 0x74);
    FUN_0015b820(s1 + 0x7C, arg1 + 0x7C);
    FUN_0015b7d0(s1 + 0x88, arg1 + 0x88);
    arg0->_setConstant = 0;
    if (arg0->_arrayIndex <= arg2) {
        arg0->_arrayIndex = arg2 + 1;
    }
}

void *FUN_0015b7d0(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    return arg0;
}

void *FUN_0015b7f0(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
    *(float *)((char *)(arg0) + 12) = (float) *(float *)((char *)(arg1) + 12);
    return arg0;
}

void *FUN_0015b820(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
    return arg0;
}

/* The product is computed into a local first and the +36 field is added to it. */

int Gap__Bec__ParticleArray__vfunc_24(ParticleArray *arg0, unsigned int arg1) {
    int prod;
    if (arg1 >= (unsigned int) arg0->_arrayIndex) {
        return 0;
    }
    prod = arg1 * arg0->_particleDataSize;
    return arg0->_particleArray + prod;
}

void Gap__Bec__ParticleArray__vfunc_25(ParticleArray *arg0) {
    arg0->_setConstant = 0;
}

bool FUN_0015bb50(A_15bb50 *arg0, V_15bb50 *arg1, float *arg2) {
    bool ok = true;
    if (arg0->b->f44 > 1) {
        *arg2 = arg1->y + arg1->x * arg0->f28;
    } else {
        *arg2 = arg1->y;
    }
    unsigned fl = arg0->f80;
    if (fl & 2) {
        float t = *arg2;
        if (t < arg0->f20 || !(t <= arg0->f24)) ok = false;
    }
    if (fl & 1) {
        if (ok) *arg2 = fmodf(*arg2, 1.0f);
    }
    return ok;
}

