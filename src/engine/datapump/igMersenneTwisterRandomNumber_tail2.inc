void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed) {
    int i; for (i = 0; i < 624; i++) { self->_mt[i] = seed & 0xFFFF0000; seed = 69069 * seed + 1; self->_mt[i] |= (seed & 0xFFFF0000) >> 16; seed = 69069 * seed + 1; } self->_mti = 624;
}

void Gap__igMersenneTwisterRandomNumber__vfunc_13(void **arg0) {
    Gap__Core__igObject__vfunc_11();
    ((DW4VC_92_1 *)(arg0))->vX((int)(0x141E));
}

unsigned int FUN_001e6bc0(igMersenneTwisterRandomNumber *self) {
    static const unsigned int mag01[2] = {0x0, 0x9908b0df};
    unsigned int y;
    int kk;

    if (self->_mti >= 624) {
        for (kk = 0; kk < 624 - 397; kk++) {
            y = (self->_mt[kk] & 0x80000000) | (self->_mt[kk + 1] & 0x7fffffff);
            self->_mt[kk] = self->_mt[kk + 397] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < 624 - 1; kk++) {
            y = (self->_mt[kk] & 0x80000000) | (self->_mt[kk + 1] & 0x7fffffff);
            self->_mt[kk] = self->_mt[kk + (397 - 624)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (self->_mt[624 - 1] & 0x80000000) | (self->_mt[0] & 0x7fffffff);
        self->_mt[624 - 1] = self->_mt[397 - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        self->_mti = 0;
    }
    y = self->_mt[self->_mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);
    return y;
}

int Vec3f_FromString(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return sscanf(arg0, arg2, arg1, arg1 + 1, arg1 + 2) == 3;
    }
    return FUN_0018be80(arg0, arg1, 3, 4, 1) != 0;
}

int FUN_001e6d80(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return sscanf(arg0, arg2, arg1, arg1 + 1, arg1 + 2, arg1 + 3) == 4;
    }
    return FUN_0018be80(arg0, arg1, 4, 4, 1) != 0;
}

int FUN_001e6de0(int *result, Vector3f *value, int *format) {
    int name;
    int res;
    int pool;
    igSmartPointer<FormattedObject> formatted((FormattedObject *)FUN_002b9500(0), AdoptReference());
    int x = fptodp(value->x);
    int y = fptodp(value->y);
    FUN_0030b7e0(formatted.p, format, x, y, fptodp(value->z));
    name = formatted.p->f8;
    if (name == 0) {
        name = g_stringObjEmptyText[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = StringPool_Allocate(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        res = StringPool_Intern(g_stringPool[0], name);
    }
    *result = res;
    return 0;
}

int FUN_001e6f10(int *result, Quad *quad, int *kind) {
    int s3, s2, s1;
    int name;
    int res;
    int obj;
    Tag tag = Tag();
    igSmartPointer<QuadNamed> named((QuadNamed *)FUN_002b9500(0));
    s3 = fptodp(quad->x);
    s2 = fptodp(quad->y);
    s1 = fptodp(quad->z);
    FUN_0030b7e0(named.p, kind, s3, s2, s1, fptodp(quad->w));
    name = named.get()->name;
    if (name == 0) {
        name = g_stringObjEmptyText[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (g_stringPool[0] == 0) {
            obj = StringPool_Allocate(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            g_stringPool[0] = obj;
        }
        res = StringPool_Intern(g_stringPool[0], name);
    }
    *result = res;
    return 0;
}

int thunk_FUN_003065f0()
{
    return FUN_003065f0();
}

int thunk_FUN_003066b0()
{
    return FUN_003066b0();
}

int thunk_FUN_00306770()
{
    return FUN_00306770();
}

int thunk_FUN_00306910()
{
    return FUN_00306910();
}

int thunk_FUN_00306e50()
{
    return FUN_00306e50();
}

int FUN_001e70a0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    void *sp6C;
    void *sp68;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;

    sp6C = (void *)(0);
    FUN_001e6de0((int *)&sp68, (Vector3f *)arg4, &DAT_004e4ac0[0]);
    if (FUN_00306910(arg0, arg1, arg2, &sp6C, sp68, arg5) != 0) {
        temp_s0 = Vec3f_FromString((int)sp6C, (int *)arg3, (int)&DAT_004e4ad0[0]) & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    return 0;
}

int FUN_001e71f0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    void *sp6C;
    void *sp68;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;

    sp6C = (void *)(0);
    FUN_001e6f10((int *)&sp68, (Quad *)arg4, &DAT_004e4ae8[0]);
    if (FUN_00306910(arg0, arg1, arg2, &sp6C, sp68, arg5) != 0) {
        temp_s0 = FUN_001e6d80((int)sp6C, (int *)arg3, (int)&DAT_004e4b00[0]) & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    return 0;
}

