int igParticleArray_Update(igParticleArray *self, unsigned int num, unsigned int offset, int *status, float time) {
    int sp70[8];
    int temp_s0;
    O44 *a;
    O44 *t;
    O48 *b;
    O48 *u;
    self->_currentTime = time;
    if (!(time <= self->_particleLifeEnd + self->_particleLifetimeEndOffset)) {
        *status = 1;
        return 1;
    }
    if (time < self->_particleLifeStart) {
        *status = 2;
        return 1;
    }
    DAT_00560668[0] += 1;
    if (((O44 *)self->_context) == 0) {
        if (((O44 *)self->_context) == 0) {
            a = (O44 *)igVisualContext_FindFirst();
            if (a != 0) {
                a->refs = a->refs + 1;
            }
            t = ((O44 *)self->_context);
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
            self->_context = (int)a;
            if (self->_configured != 0 && ((HI *)self->_particleFormat)->f32 != 0 && ((O48 *)self->_pointSpriteInterface) == 0) {
                b = ((O44 *)self->_context)->v104("igPointSpriteExt");
                if (b != 0) {
                    b->refs = b->refs + 1;
                }
                u = ((O48 *)self->_pointSpriteInterface);
                if (u != 0) {
                    u->refs = u->refs - 1;
                    if (((unsigned long long)((long long)u->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(u);
                    }
                }
                self->_pointSpriteInterface = (int)b;
            }
        }
        if (((O44 *)self->_context) != 0) {
            if (self->_configured == 0) {
                ((PA *)self)->v92((int)((HI *)self->_particleFormat), self->_maxNum, ((O44 *)self->_context), self->_particleLifeStart, self->_particleLifeEnd);
            }
            goto L24;
        }
        *status = 1;
        return 0;
    }
L24:
    self->_particleNum = num;
    self->_aliveParticleNum = num;
    self->_particleOffset = offset;
    igVertexArrayLock_Init(sp70);
    sp70[1] = 0;
    sp70[0] = 0;
    ((O40 *)self->_internalVertexArray)->v108(sp70, 1);
    ((O40 *)self->_internalVertexArray)->v112(sp70, 2);
    temp_s0 = ((HI *)self->_particleFormat)->f44 > 0;
    if (self->_setConstant == 0 && temp_s0 == 0) {
        FUN_0015b880((PA *)self);
    }
    if (((int (*)(float, unsigned int, unsigned int, int, unsigned int, O40 *, O48 *))self->_updateFunction) != 0) {
        if (((O48 *)self->_pointSpriteInterface) != 0) {
            ((O48 *)self->_pointSpriteInterface)->v136(((HI *)self->_particleFormat)->f36);
        }
        ((int (*)(float, unsigned int, unsigned int, int, unsigned int, O40 *, O48 *))self->_updateFunction)(time, num, offset, self->_particleArray, self->_particleDataSize, ((O40 *)self->_internalVertexArray), ((O48 *)self->_pointSpriteInterface));
    } else if (temp_s0 == 0) {
        FUN_0015bc20((PA *)self, temp_s0, 1);
    } else {
        FUN_0015bc20((PA *)self, temp_s0, 0);
    }
    self->_setConstant = 1;
    *status = 0;
    return 1;
}

