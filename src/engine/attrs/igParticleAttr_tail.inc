void Gap__Attrs__igParticleAttr__vfunc_24(igParticleAttr *arg0, char *arg1) {
    int sp4C;
    float temp_f20;
    float t2;
    long long temp_s1;
    if (arg0->_bUseCurrentTime != 0) {
        if (arg0->_startTime == -1) {
            arg0->_startTime = *(long long *)(arg1 + 96);
        }
        temp_s1 = *(long long *)(arg1 + 96) - arg0->_startTime;
        temp_f20 = __floatdisf(__moddi3(temp_s1, 1000000000)) / (float)1000000000;
        t2 = __floatdisf(__divdi3(temp_s1, 1000000000));
        arg0->_time = t2 + temp_f20;
    }
    ((A_13f8a0 *)arg0->_particleArray)->vX(arg0->_particleNum, arg0->_particleOffset, &sp4C, arg0->_time + arg0->_offset);
    if (sp4C == 0) {
        ((B_13f8a0 *)arg0->_particleArray)->vX();
    }
}

void Gap__Attrs__igParticleAttr__vfunc_32(igParticleAttr *self, igObject *particleArray, int particleNum, int particleOffset) {
    igObject *previous;
    if (particleArray != 0) {
        particleArray->_refCount = particleArray->_refCount + 1;
    }
    previous = (igObject *)self->_particleArray;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        /* The shift-and-test spelling of the 23-bit count keeps the dsll32/dsrl32 pair. */
        if (((unsigned long long) ((long long)(int) previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_particleArray = (int)particleArray;
    self->_particleOffset = particleOffset;
    self->_particleNum = particleNum;
}

int Gap__Attrs__igParticleAttr__vfunc_33(void *arg0) {
    VC37 *o = *(VC37 **)((char *)arg0 + 16);
    float v = o->vX();
    float f = *(float *)((char *)arg0 + 40);
    int r = 1;
    if (v < f) r = 0;
    return r;
}

