void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed) {
    int i; for (i = 0; i < 624; i++) { self->_mt[i] = seed & 0xFFFF0000; seed = 69069 * seed + 1; self->_mt[i] |= (seed & 0xFFFF0000) >> 16; seed = 69069 * seed + 1; } self->_mti = 624;
}

void Gap__igMersenneTwisterRandomNumber__vfunc_13(void **arg0, int flags) {
    Gap__Core__igObject__resetFields((igObject *)arg0, flags);
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

int Vec3f_FromString(const char *text, float *vector, const char *format) {
    if (format != 0) {
        return sscanf(text, format, vector, vector + 1, vector + 2) == 3;
    }
    return FUN_0018be80(text, vector, 3, 4, 1) != 0;
}

int FUN_001e6d80(int arg0, int *arg1, const char *format) {
    if (format != 0) {
        return sscanf((const char *)arg0, format, arg1, arg1 + 1, arg1 + 2, arg1 + 3) == 4;
    }
    return FUN_0018be80(arg0, arg1, 4, 4, 1) != 0;
}

int FUN_001e6de0(int *result, Vector3f *value, const char *format) {
    int name;
    int res;
    int pool;
    igSmartPointer<FormattedObject> formatted((FormattedObject *)igStringObj_Create(0), AdoptReference());
    double x = fptodp(value->x);
    double y = fptodp(value->y);
    igStringObj_Format(formatted.p, format, x, y, fptodp(value->z));
    name = formatted.p->f8;
    if (name == 0) {
        name = (int)g_stringObjEmptyText;
    }
    if (name == 0) {
        res = 0;
    } else {
        if (g_stringPool == 0) {
            pool = (int)(StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = (int)(StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        res = (int)(StringPool_Intern(g_stringPool, (const char *)name));
    }
    *result = res;
    return 0;
}

int FUN_001e6f10(int *result, Quad *quad, const char *kind) {
    double s3, s2, s1;
    int name;
    int res;
    int obj;
    Tag tag = Tag();
    igSmartPointer<QuadNamed> named((QuadNamed *)igStringObj_Create(0));
    s3 = fptodp(quad->x);
    s2 = fptodp(quad->y);
    s1 = fptodp(quad->z);
    igStringObj_Format(named.p, kind, s3, s2, s1, fptodp(quad->w));
    name = named.get()->name;
    if (name == 0) {
        name = (int)g_stringObjEmptyText;
    }
    if (name == 0) {
        res = 0;
    } else {
        if (g_stringPool == 0) {
            obj = (int)(StringPool_Allocate(0x10));
            if (obj != 0) {
                obj = (int)(StringPool_Construct((StringPool *)obj));
            }
            g_stringPool = (StringPool *)obj;
        }
        res = (int)(StringPool_Intern(g_stringPool, (const char *)name));
    }
    *result = res;
    return 0;
}

bool thunk_igRegistry_GetValueInt(igRegistry *registry, int section, const char *key, int *out, int defaultValue, int create)
{
    return igRegistry_GetValueInt(registry, section, key, out, defaultValue, create);
}

bool thunk_igRegistry_GetValueFloat(igRegistry *registry, int section, const char *key, float *out, int create, float defaultValue)
{
    return igRegistry_GetValueFloat(registry, section, key, out, create, defaultValue);
}

int thunk_igRegistry_GetValueStringObj(igRegistry *registry, int section, const char *key, igStringObj **out, const char *defaultValue, int create)
{
    return igRegistry_GetValueStringObj(registry, section, key, out, defaultValue, create);
}

int thunk_igRegistry_GetValueString(igRegistry *registry, int section, const char *key, char **out, char *def, int create)
{
    return igRegistry_GetValueString(registry, section, key, out, def, create);
}

unsigned char thunk_igRegistry_GetValueBool(igRegistry *registry, int section, const char *name, unsigned char *value, int defaultValue, int create)
{
    return igRegistry_GetValueBool(registry, section, name, value, defaultValue, create);
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
    FUN_001e6de0((int *)&sp68, (Vector3f *)arg4, "<%f,%f,%f>");
    if (igRegistry_GetValueString((igRegistry *)arg0, arg1, (const char *)arg2, (char **)&sp6C, (char *)sp68, arg5) != 0) {
        temp_s0 = Vec3f_FromString((const char *)sp6C, (float *)arg3, " < %f , %f , %f > ") & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_2), (StringTokenHeader *)temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_3), (StringTokenHeader *)temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_4), (StringTokenHeader *)temp_a1_4);
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
    FUN_001e6f10((int *)&sp68, (Quad *)arg4, "<%f,%f,%f,%f>");
    if (igRegistry_GetValueString((igRegistry *)arg0, arg1, (const char *)arg2, (char **)&sp6C, (char *)sp68, arg5) != 0) {
        temp_s0 = FUN_001e6d80((int)sp6C, (int *)arg3, " < %f , %f , %f , %f > ") & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_2), (StringTokenHeader *)temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_3), (StringTokenHeader *)temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_4), (StringTokenHeader *)temp_a1_4);
        }
    }
    return 0;
}

