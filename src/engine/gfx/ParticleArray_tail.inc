void Gap__Bec__ParticleArray__vfunc_28(ParticleArray *arg0, RefCountedHeader *arg1, int arg2, int arg3) {
    RefCountedHeader *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (RefCountedHeader *)((void *)(arg0->_primLengthArray));
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_primLengthArray = (int)(arg1);
    arg0->_primLengthArrayNum = arg2;
    arg0->_primLengthArrayOffset = arg3;
}

int Gap__Bec__ParticleArray__vfunc_30(ParticleArray *p)
{
    return p->_particleFormat;
}

int Gap__Bec__ParticleArray__vfunc_29(ParticleArray *p)
{
    return p->_maxNum;
}

static inline igObject *f24_of(const PointSpriteInterfaceView *view) { return view->f24; }

void Gap__Bec__ParticleArray__vfunc_10(ParticleArray *arg0) {
    void *temp_a0;
    igObject *temp_a0_2;
    PointSpriteInterfaceView *temp_s0;

    temp_a0 = (void *)arg0->_particleArray;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->_particleArray = 0;
    temp_s0 = (PointSpriteInterfaceView *)arg0->_pointSpriteInterface;
    if ((temp_s0 != 0) && (f24_of(temp_s0) == (igObject *)arg0->_internalVertexArray)) {
        temp_a0_2 = temp_s0->f24;
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
            if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        temp_s0->f24 = 0;
    }
}

