static inline unsigned int clutSize(const struct S_154980 *c) { return c->f24; }

int Gap__Gfx__igClut__vfunc_25(struct S_154980 *arg0, int arg1, int arg2, int arg3) {
    int sp5C;
    int sp58;
    if (arg3 != 0 && arg0->f20 == arg3 && arg1 == arg0->f8 && arg1 != -1) {
        FUN_00154e40((S0_154e40 *)arg0, arg2);
        return 1;
    }
    if (arg0->f20 != 0) {
        FUN_00300f50(arg0, arg0->f20);
    }
    arg0->f8 = arg1;
    arg0->f12 = arg2;
    FUN_00154b80(arg1, arg2, &sp5C, &sp58);
    arg0->f24 = sp5C;
    arg0->f16 = sp58;
    arg0->f20 = FUN_00300db0(arg0, arg0->f24, 0x80);
    if (arg3 != 0) {
        memcpy(arg0->f20, arg3, clutSize(arg0));
    } else {
        memset(arg0->f20, 0, clutSize(arg0));
    }
    return 1;
}

int Gap__Gfx__igClut__vfunc_24(void **arg0) {
    int temp_s0;

    temp_s0 = ((DW4VC_100_0 *)(arg0))->vX() & 0xFF;
    FUN_00154d40((Obj_154d40 *)arg0);
    return temp_s0;
}

unsigned char igClut_UnscaleAlpha(igClut *clut)
{
    unsigned int i;
    unsigned char *entry;
    unsigned char unscaled = 0;

    if (clut->_fmt == 7) {
        entry = (unsigned char *)clut->_pData;
        for (i = 0; i < clut->_numEntries; i++) {
            entry[3] = (entry[3] & 0x80) ? ~(entry[3] & 0xFF) << 1 : entry[3] << 1;
            entry += 4;
        }
        unscaled = 1;
    } else if (clut->_fmt != 5) {
        return 0;
    }
    return unscaled;
}

int FUN_00154b40(Obj_154b40 *arg0) {
    int temp_v0;
    if (arg0->f29 != 0) {
        temp_v0 = igClut_UnscaleAlpha((igClut *)arg0);
        arg0->f29 = 0U;
        return temp_v0 & 0xFF;
    }
    return 1;
}

int FUN_00154b80(int arg0, int arg1, int *arg2, int *arg3) {
    switch (arg0) {
    case 0x0: *arg3 = 1; break;
    case 0x1: *arg3 = 1; break;
    case 0x2: *arg3 = 1; break;
    case 0x3: *arg3 = 2; break;
    case 0x4: *arg3 = 1; break;
    case 0x5: *arg3 = 3; break;
    case 0x6: *arg3 = 1; break;
    case 0x7: *arg3 = 4; break;
    case 0x8: *arg3 = 2; break;
    case 0x10000: *arg3 = 1; break;
    case 0x10001: *arg3 = 1; break;
    default:
        *arg2 = -2;
        *arg3 = -2;
        return *arg2;
    }
    *arg2 = arg1 * *arg3;
    return *arg2;
}

void FUN_00154c90(igClut *arg0, igClut *arg1, int arg2) {
    int temp_a1;
    unsigned int sz;

    if (arg0 != arg1) {
        temp_a1 = arg0->_pData;
        if (temp_a1 != 0) {
            FUN_00300f50(arg0, temp_a1);
            arg0->_pData = 0;
        }
        arg0->_fmt = arg1->_fmt;
        arg0->_numEntries = arg1->_numEntries;
        arg0->_stride = arg1->_stride;
        arg0->_clutSize = arg1->_clutSize;
        arg0->_isAlphaScaled = arg1->_isAlphaScaled;
        if (arg2 != 0) {
            arg0->_pData = FUN_00300db0(arg0, arg0->_clutSize, 0x80);
            sz = arg0->_clutSize;
            memcpy(arg0->_pData, arg1->_pData, sz);
        }
    }
}

int FUN_00154d40(Obj_154d40 *arg0) {
    int temp_v0;
    if (arg0->f29 == 0) {
        temp_v0 = FUN_00154d90((igClut *)arg0) & 0xFF;
        arg0->f29 = 1U;
        return temp_v0;
    }
    return 1;
}

unsigned char FUN_00154d90(igClut *clut)
{
    unsigned int i;
    unsigned char *entry;
    unsigned char scaled = 0;

    if (clut->_fmt == 7) {
        entry = (unsigned char *)clut->_pData;
        for (i = 0; i < clut->_numEntries; i++) {
            entry[3] = (entry[3] >> 1) + (entry[3] & 1);
            entry += 4;
        }
        scaled = 1;
    } else if (clut->_fmt != 5) {
        return 0;
    }
    return scaled;
}

void Gap__Gfx__igClut__vfunc_12(S0 *arg0) {
    int temp_a1;

    temp_a1 = arg0->f14;
    if (temp_a1 != 0) {
        FUN_00300f50(arg0, temp_a1);
        arg0->f14 = 0;
    }
}

void FUN_00154e40(S0_154e40 *arg0, int arg1) {
    if (arg1 != arg0->fC) {
        arg0->f14 = FUN_00300ea0(arg0, arg0->f14, arg1 * arg0->f10, 0x80);
        arg0->fC = arg1;
        arg0->f18 = (int)((int) (arg1 * arg0->f10));
    }
}

int Gap__Gfx__igClut__vfunc_23(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = FUN_0015ad50((char *)arg1);
    if (temp_v0 != 0) {
        if (strcmp(temp_v0, &text_act[0]) != 0) {
            if (strcmp(temp_v0, &ACT[0]) == 0) {
                goto block_4;
            }
            goto block_5;
        }
block_4:
        return FUN_00154f30((Arr *)arg0, arg1);
    }
block_5:
    return 0;
}

int FUN_00154f30(Arr *self, int arg1) {
    int a, b;
    int i;
    int *p;
    a = igObject_GetAllocator();
    if (g_useOwnerAllocator != 0) { b = a; } else { b = (int)Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]); } a = b;
    igSmartPointer<DW4VC_100_2> h((DW4VC_100_2 *)igFile_Create(a), kRetainReference);
    { DW4VC_100_2 *x = h.p; --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); }
    if (self->a20 != 0) FUN_00300f50(self, self->a20);
    self->a20 = 0;
    if (h.p->vX(arg1, (int)&DAT_004de6c0[0]) == 0) {
        return 0;
    }
    self->a20 = (void *)FUN_00300db0(self, 0x400, 0x80);
    p = (int *)self->a20;
    i = 0;
    do {
        h.p->v25((int)p, 1, 3);
        i++;
        *((unsigned char *)p + 3) = 0xff;
        p++;
    } while ((unsigned)i < 0x100);
    if ((unsigned)i < 0x100) memset(p, 0, (0x100 - i) * 4);
    self->a24 = 0x400;
    self->a16 = 4;
    self->a12 = 0x100;
    self->a8 = 7;
    h.p->v24();
    return 1;
}

