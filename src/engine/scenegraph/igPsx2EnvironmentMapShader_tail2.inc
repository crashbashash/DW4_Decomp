void igPsx2EnvironmentMapShader_userDestruct(void **arg0) {
    if (igMetaObject_CountInstances((igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX()), 1) == 0) {
        ((DW4VC_200_0 *)(arg0))->vX();
    }
    FUN_001c1c60((T_1c1c60 *)arg0);
}

int igPsx2EnvironmentMapShader_GetMeta(void) {
    return ((int)g_igPsx2EnvironmentMapShader_metaObject);
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_49(void) {
    int temp_s0;
    int temp_s0_10;
    int temp_s0_11;
    int temp_s0_2;
    int temp_s0_3;
    int temp_s0_4;
    int temp_s0_5;
    int temp_s0_6;
    int temp_s0_7;
    int temp_s0_8;
    int temp_s0_9;

    FUN_001c1e10();
    if (g_envMapMatrixOptStateAttr.p == 0) {
        temp_s0 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapMatrixOptStateAttr.release();
        g_envMapMatrixOptStateAttr.p = (igMatrixOptStateAttr *)Gap::Attrs::igMatrixOptStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0);
        ((DW4VC_128_1 *)g_envMapMatrixOptStateAttr.p)->vX(0);
        temp_s0_2 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapTextureMatrixStateAttr.release();
        g_envMapTextureMatrixStateAttr.p = (igTextureMatrixStateAttr *)Gap::Attrs::igTextureMatrixStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_2);
        ((DW4VC_128_1 *)g_envMapTextureMatrixStateAttr.p)->vX(0);
        ((DW4VC_100_1 *)g_envMapTextureMatrixStateAttr.p)->vX(0);
    }
    if (g_envMapBlendZeroSrcAlphaUnit1.p == 0) {
        temp_s0_3 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapBlendZeroSrcAlphaUnit1.release();
        g_envMapBlendZeroSrcAlphaUnit1.p = (igBlendFunctionAttr *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_3);
        ((DW4VC_100_1 *)g_envMapBlendZeroSrcAlphaUnit1.p)->vX(1);
        ((DW4VC_128_1 *)g_envMapBlendZeroSrcAlphaUnit1.p)->vX(0);
        ((DW4VC_132_1 *)g_envMapBlendZeroSrcAlphaUnit1.p)->vX(4);
    }
    if (g_envMapPixelPipelineModeAttr.p == 0) {
        temp_s0_4 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapPixelPipelineModeAttr.release();
        g_envMapPixelPipelineModeAttr.p = (igPixelPipelineModeAttr *)Gap::Attrs::igPixelPipelineModeAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_4);
        ((T_1e08b0 *)g_envMapPixelPipelineModeAttr.p)->f12 = 3;
    }
    if (g_envMapTextureUnit1On.p == 0) {
        temp_s0_5 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapTextureUnit1On.release();
        g_envMapTextureUnit1On.p = (igTextureStateAttr *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_5);
        ((DW4VC_128_1 *)g_envMapTextureUnit1On.p)->vX(1);
        ((DW4VC_100_1 *)g_envMapTextureUnit1On.p)->vX(1);
    }
    if (g_envMapTextureUnit2On.p == 0) {
        temp_s0_6 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapTextureUnit2On.release();
        g_envMapTextureUnit2On.p = (igTextureStateAttr *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_6);
        ((DW4VC_128_1 *)g_envMapTextureUnit2On.p)->vX(1);
        ((DW4VC_100_1 *)g_envMapTextureUnit2On.p)->vX(2);
    }
    if (g_envMapTextureUnit1Off.p == 0) {
        temp_s0_7 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapTextureUnit1Off.release();
        g_envMapTextureUnit1Off.p = (igTextureStateAttr *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_7);
        ((DW4VC_128_1 *)g_envMapTextureUnit1Off.p)->vX(0);
        ((DW4VC_100_1 *)g_envMapTextureUnit1Off.p)->vX(1);
    }
    if (g_envMapTextureUnit2Off.p == 0) {
        temp_s0_8 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapTextureUnit2Off.release();
        g_envMapTextureUnit2Off.p = (igTextureStateAttr *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_8);
        ((DW4VC_128_1 *)g_envMapTextureUnit2Off.p)->vX(0);
        ((DW4VC_100_1 *)g_envMapTextureUnit2Off.p)->vX(2);
    }
    if (g_envMapBlendOneOneUnit1.p == 0) {
        temp_s0_9 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapBlendOneOneUnit1.release();
        g_envMapBlendOneOneUnit1.p = (igBlendFunctionAttr *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_9);
        ((DW4VC_100_1 *)g_envMapBlendOneOneUnit1.p)->vX(1);
        ((DW4VC_128_1 *)g_envMapBlendOneOneUnit1.p)->vX(1);
        ((DW4VC_132_1 *)g_envMapBlendOneOneUnit1.p)->vX(1);
    }
    if (g_envMapBlendOneOneUnit2.p == 0) {
        temp_s0_10 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapBlendOneOneUnit2.release();
        g_envMapBlendOneOneUnit2.p = (igBlendFunctionAttr *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_10);
        ((DW4VC_100_1 *)g_envMapBlendOneOneUnit2.p)->vX(2);
        ((DW4VC_128_1 *)g_envMapBlendOneOneUnit2.p)->vX(1);
        ((DW4VC_132_1 *)g_envMapBlendOneOneUnit2.p)->vX(1);
    }
    if (g_envMapColorMaskAttr.p == 0) {
        temp_s0_11 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_envMapColorMaskAttr.release();
        g_envMapColorMaskAttr.p = (igColorMaskAttr *)Gap::Attrs::igColorMaskAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0_11);
        ((DW4VC_128_4 *)g_envMapColorMaskAttr.p)->vX(0, 0, 0, 1);
    }
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_50(int arg0) {
    g_envMapMatrixOptStateAttr.clear();
    g_envMapTextureMatrixStateAttr.clear();
    g_envMapTextureUnit1On.clear();
    g_envMapTextureUnit2On.clear();
    g_envMapTextureUnit1Off.clear();
    g_envMapTextureUnit2Off.clear();
    g_envMapBlendOneOneUnit1.clear();
    g_envMapBlendOneOneUnit2.clear();
    g_envMapColorMaskAttr.clear();
    g_envMapPixelPipelineModeAttr.clear();
    g_envMapBlendZeroSrcAlphaUnit1.clear();
    FUN_001c1f90(arg0);
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_51(S_1e1210 *self) {
    int alloc;
    Rc_1e1210 *t;
    A_1e1210 *a;
    FUN_001c20b0((Controller *)self);
    *(int *)((char *)self->f32 + 96) = 2;
    if ((((A_1e1210 *)((Gap::Attrs::igTextureAttr *)self->f32)->getImage(0)) != 0) == 0) FUN_001c31e0((igTextureAttr *)self->f32);
    if (self->f52 != 0 && ((A_1e1210 *)((Gap::Attrs::igTextureAttr *)self->f52)->getImage(0)) != 0 && *(int *)((char *)((A_1e1210 *)((Gap::Attrs::igTextureAttr *)self->f52)->getImage(0)) + 44) == 0) {
        a = ((A_1e1210 *)((Gap::Attrs::igTextureAttr *)self->f52)->getImage(0));
        a->v28(1);
    }
    if (self->f73 != 0) ((Gap::Attrs::igTextureCubeAttr *)self->f32)->releaseImage(Gap::Attrs::igTextureCubeAttr::CUBE_MAP);
    self->f80->v30(2);
    alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    t = self->f116;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)t);
    }
    self->f116 = (Rc_1e1210 *)Gap::Attrs::igTexGenMatrixAttr::_instantiateFromPool((igMemoryPoolView *)alloc);
    alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    t = (Rc_1e1210 *)self->f112;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)t);
    }
    self->f112 = ((B_1e1210 *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool((igMemoryPoolView *)alloc));
    self->f112->v30(1);
    self->f112->v31(1);
    alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    t = self->f120;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)t);
    }
    self->f120 = (Rc_1e1210 *)Gap::Attrs::igMultiPassStateAttr::_instantiateFromPool((igMemoryPoolView *)alloc);
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_52(S_1e1400 *arg0) {
    R_1e1400 *p;

    FUN_001c2880((S_1c2880 *)arg0);
    p = arg0->a;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)p);
        }
    }
    arg0->a = 0;
    p = arg0->b;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)p);
        }
    }
    arg0->b = 0;
    p = arg0->c;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)p);
        }
    }
    arg0->c = 0;
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_45(igPsx2EnvironmentMapShader *arg0, EnvMapSource *arg1) {
    float m[16];
    float *row;
    void **temp_a0;

    if (GPR_00554bb0 == 0) {
        DAT_004e48a0[0] = 0;
        DAT_004e48ac[0] = 1.0f;
        DAT_004e48a4[0] = 0;
        GPR_00554bb0 = 1;
        DAT_004e48a8[0] = 0;
    }
    igMatrix44f_Copy(m, arg1->matrix);
    row = &m[12];
    row[0] = DAT_004e48a0[0];
    row[1] = DAT_004e48a4[0];
    row[2] = DAT_004e48a8[0];
    row[3] = DAT_004e48ac[0];
    temp_a0 = (void **)(arg0->_envMapTexGenMatrix);
    ((DW4VC_128_1 *)(temp_a0))->vX((int)(m));
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_48(S_1e1580 *self, A1_1e1580 *arg1) {
    int v;
    unsigned char fl;
    self->v50();
    self->f60 = 1;
    if (self->f32 != 0) {
        self->v47(arg1);
        self->v49(arg1);
        self->f72 = 1;
        v = arg1->vX(22);
        fl = self->f48;
        if (fl == 0 && v > 2 && self->f52 != 0) {
            FUN_001e22c0((EnvMapShaderView_1e22c0 *)self, (void *)arg1);
            return;
        }
        if (self->f52 != 0) {
            FUN_001e1e70((EnvMapShaderView_1e1e70 *)self, (void *)arg1);
            return;
        }
        if (fl == 0 && v > 1) {
            FUN_001e16a0((EnvMapShaderView *)self, (void *)arg1);
            return;
        }
        FUN_001e1ac0((S_1e1ac0 *)self, (void *)arg1);
    }
}

void FUN_001e16a0(EnvMapShaderView *arg0, void *) {
    float f;
    unsigned int v;
    EnvMapRef attrListA;
    attrListA.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    EnvMapRef attrListB;
    attrListB.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)attrListA.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)attrListB.p);
    arg0->f120->vX(2);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f120);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f120);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)g_envMapPixelPipelineModeAttr.p);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)g_envMapPixelPipelineModeAttr.p);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f76);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f76);
    arg0->f84->f12 = 0;
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f84);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f84);
    f = arg0->f44;
    if (f != 1.0f) {
        if (!(f <= 1.0f) || f < 0.0f) {
            arg0->f44 = 1.0f;
        }
        arg0->f112->vX(11);
        v = (unsigned int)(128.0f * arg0->f44);
        ((EnvMapAlphaAttr *)arg0->f112)->b28 = (unsigned char)v;
    } else {
        arg0->f112->vX(1);
    }
    arg0->f112->vY(0);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)g_envMapBlendOneOneUnit1.p);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)g_envMapBlendOneOneUnit1.p);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
    ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
    if (arg0->f36 != 0) {
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1On.p);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1On.p);
        EnvMapRef texBindAttr;
        texBindAttr.p = ((EnvMapAttr *)Gap::Attrs::igTextureBindAttr::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
        ((EnvMapAttrOps *)texBindAttr.p)->d23(1);
        ((EnvMapAttrOps *)texBindAttr.p)->vY(arg0->f36->f12);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)texBindAttr.p);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)texBindAttr.p);
        arg0->f92->d23(1);
        arg0->f88->d23(1);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f88);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f88);
    } else {
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1Off.p);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1Off.p);
    }
}

void FUN_001e1ac0(S_1e1ac0 *arg0, void *) {
    float f;
    unsigned int v;
    Ref_1e1ac0 attrListA;
    attrListA.p = ((X_1e1ac0 *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    Ref_1e1ac0 attrListB;
    attrListB.p = ((X_1e1ac0 *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)attrListA.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)attrListB.p);
    Ref_1e1ac0 attrListC;
    attrListC.p = ((X_1e1ac0 *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    Ref_1e1ac0 attrListD;
    attrListD.p = ((X_1e1ac0 *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)attrListC.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)attrListD.p);
    ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)(((X_1e1ac0 *)g_envMapMatrixOptStateAttr.p)));
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)(((X_1e1ac0 *)g_envMapMatrixOptStateAttr.p)));
    if (arg0->f36 != 0) {
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562730)[0]));
        ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562730)[0]));
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f36);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f36);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f96);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f96);
        ((Gap::Core::igObjectList *)attrListA.p)->append((Gap::Core::igObject *)arg0->f88);
        ((Gap::Core::igObjectList *)attrListB.p)->append((Gap::Core::igObject *)arg0->f88);
    } else {
        ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562730)[0]));
        ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562730)[0]));
    }
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562738)[0]));
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)(((X_1e1ac0 * *)DAT_00562738)[0]));
    f = arg0->f44;
    if (f != 1.0f) {
        if (!(f <= 1.0f) || f < 0.0f) {
            arg0->f44 = 1.0f;
        }
        arg0->f112->vX(11);
        v = (unsigned int)(128.0f * arg0->f44);
        ((W112 *)arg0->f112)->b28 = (unsigned char)v;
    }
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)(((X_1e1ac0 *)g_envMapTextureMatrixStateAttr.p)));
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)(((X_1e1ac0 *)g_envMapTextureMatrixStateAttr.p)));
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)arg0->f76);
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)arg0->f76);
    arg0->f84->f12 = 0;
    ((Gap::Core::igObjectList *)attrListC.p)->append((Gap::Core::igObject *)arg0->f84);
    ((Gap::Core::igObjectList *)attrListD.p)->append((Gap::Core::igObject *)arg0->f84);
}

void FUN_001e1e70(EnvMapShaderView_1e1e70 *arg0, void *) {
    EnvMapRef r60;
    r60.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    EnvMapRef r56;
    r56.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)r60.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)r56.p);
    EnvMapRef r52;
    r52.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    EnvMapRef r48;
    r48.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)r52.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)r48.p);
    EnvMapRef r44;
    r44.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    EnvMapRef r40;
    r40.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)r44.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)r40.p);
    ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapMatrixOptStateAttr.p)));
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapMatrixOptStateAttr.p)));
    if (arg0->f36 != 0) {
        ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
        ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
        ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)arg0->f36);
        ((Gap::Core::igObjectList *)r56.p)->append((Gap::Core::igObject *)arg0->f36);
        ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)r56.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)arg0->f96);
        ((Gap::Core::igObjectList *)r56.p)->append((Gap::Core::igObject *)arg0->f96);
        ((Gap::Core::igObjectList *)r60.p)->append((Gap::Core::igObject *)arg0->f88);
        ((Gap::Core::igObjectList *)r56.p)->append((Gap::Core::igObject *)arg0->f88);
    } else {
        ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
        ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
    }
    arg0->f84->f12 = 0;
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)arg0->f84);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)arg0->f84);
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)(((EnvMapAttr * *)DAT_00562740)[0]));
    ((Gap::Core::igObjectList *)r48.p)->append((Gap::Core::igObject *)(((EnvMapAttr * *)DAT_00562740)[0]));
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)arg0->f104);
    ((Gap::Core::igObjectList *)r48.p)->append((Gap::Core::igObject *)arg0->f104);
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)arg0->f100);
    ((Gap::Core::igObjectList *)r48.p)->append((Gap::Core::igObject *)arg0->f100);
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapColorMaskAttr.p)));
    ((Gap::Core::igObjectList *)r48.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapColorMaskAttr.p)));
    ((Gap::Core::igObjectList *)r52.p)->append((Gap::Core::igObject *)g_igAlphaStateAttr_instance.p);
    ((Gap::Core::igObjectList *)r48.p)->append((Gap::Core::igObject *)g_igAlphaStateAttr_instance.p);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    arg0->f112->vX(8);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)r44.p)->append((Gap::Core::igObject *)arg0->f76);
    ((Gap::Core::igObjectList *)r40.p)->append((Gap::Core::igObject *)arg0->f76);
}

void FUN_001e22c0(EnvMapShaderView_1e22c0 *arg0, void *) {
    EnvMapRef a;
    EnvMapRef b;
    if (arg0->f104 == arg0->f88) {
        assignRef_1e22c0(arg0->f104, EnvMapTempRef(((EnvMapAttr *)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()))));
        arg0->f104->vX(0);
        arg0->f104->vY(arg0->f56);
    }
    a.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    b.p = ((EnvMapAttr *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)a.p);
    ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)b.p);
    arg0->f120->vX(3);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f120);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f120);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)g_envMapPixelPipelineModeAttr.p);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)g_envMapPixelPipelineModeAttr.p);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)DAT_00562738[0]);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f116);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)DAT_00562730[0]);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f80);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)g_envMapTextureMatrixStateAttr.p);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f76);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f76);
    arg0->f84->f12 = 0;
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f84);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f84);
    arg0->f112->vX(1);
    arg0->f112->vY(0);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f112);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)g_igAlphaStateAttr_instance.p);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)g_igAlphaStateAttr_instance.p);
    arg0->f104->d23(1);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f104);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f104);
    arg0->f100->d23(1);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f100);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f100);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1On.p);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)g_envMapTextureUnit1On.p);
    arg0->f108->d23(1);
    ((EnvMapAttrState *)arg0->f108)->f12 = 0;
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f108);
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f108);
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapBlendZeroSrcAlphaUnit1.p)));
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapBlendZeroSrcAlphaUnit1.p)));
    ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapBlendOneOneUnit2.p)));
    ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapBlendOneOneUnit2.p)));
    if (arg0->f36 != 0) {
        ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapTextureUnit2On.p)));
        ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapTextureUnit2On.p)));
        EnvMapRef c;
        c.p = ((EnvMapAttr *)Gap::Attrs::igTextureBindAttr::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
        ((EnvMapAttrOps *)c.p)->d23(2);
        ((EnvMapAttrOps *)c.p)->vY(arg0->f36->f12);
        ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)c.p);
        ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)c.p);
        arg0->f92->d23(2);
        arg0->f88->d23(2);
        ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f92);
        ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)arg0->f88);
        ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)arg0->f88);
    } else {
        ((Gap::Core::igObjectList *)a.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapTextureUnit2Off.p)));
        ((Gap::Core::igObjectList *)b.p)->append((Gap::Core::igObject *)(((EnvMapAttr *)g_envMapTextureUnit2Off.p)));
    }
}

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_46(void) {
}

int FUN_001e2810(void) {
    return 0;
}

void igPsx2EnvironmentMapShader_Reset(igPsx2EnvironmentMapShader *self) {
    self->_configured = 0;
}

int igPsx2EnvironmentMapShader_IsTransformable(void) {
    return 0;
}

int igGroup_HasChildren(igGroup *self) {
    int var_v0;
    void *temp_v0;

    temp_v0 = (void *)(self->_childList);
    if (temp_v0 != 0) {
        var_v0 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_v0 = 0;
    }
    return var_v0 > 0;
}

int igGroup_IsChildrenOrdered(void) {
    return 0;
}

void igNode_SetFlags(int a0, int a1)
{
    *(int *)((char *)a0 + 20) = a1;
}

