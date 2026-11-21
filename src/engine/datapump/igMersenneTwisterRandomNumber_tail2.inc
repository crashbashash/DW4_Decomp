void igMersenneTwisterRandomNumber_Seed(igMersenneTwisterRandomNumber *self, unsigned int seed) {
    int i; for (i = 0; i < 624; i++) { self->_mt[i] = seed & 0xFFFF0000; seed = 69069 * seed + 1; self->_mt[i] |= (seed & 0xFFFF0000) >> 16; seed = 69069 * seed + 1; } self->_mti = 624;
}

void igMersenneTwisterRandomNumber_resetFields(igMersenneTwisterRandomNumber *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    ((igRandomNumberDispatchView *)self)->sgenrand(5150);
}

unsigned int igMersenneTwisterRandomNumber_GetNumberNonVirtual(igMersenneTwisterRandomNumber *self) {
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

int igConvertString_Vec3f(const char *text, float *vector, const char *format) {
    if (format != 0) {
        return sscanf(text, format, vector, vector + 1, vector + 2) == 3;
    }
    return FUN_0018be80(text, vector, 3, 4, 1) != 0;
}

int igConvertString_Vec4f(const char *text, float *vector, const char *format) {
    if (format != 0) {
        return sscanf(text, format, vector, vector + 1, vector + 2, vector + 3) == 4;
    }
    return FUN_0018be80(text, vector, 4, 4, 1) != 0;
}

int igConvertToString_Vec3f(char **result, const float *vector, const char *format) {
    const char *text;
    char *interned;
    int pool;
    igSmartPointer<FormattedObject> formatted((FormattedObject *)igStringObj_Create(0), AdoptReference());
    double x = fptodp(vector[0]);
    double y = fptodp(vector[1]);
    igStringObj_Format((igStringObj *)formatted.p, format, x, y, fptodp(vector[2]));
    text = (const char *)formatted.p->buffer;
    if (text == 0) {
        text = g_stringObjEmptyText;
    }
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = (int)(StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = (int)(StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = StringPool_Intern(g_stringPool, text);
    }
    *result = interned;
    return 0;
}

int igConvertToString_Vec4f(char **result, const float *vector, const char *format) {
    double x, y, z;
    const char *text;
    char *interned;
    int pool;
    Tag tag = Tag();
    igSmartPointer<QuadNamed> formatted((QuadNamed *)igStringObj_Create(0));
    x = fptodp(vector[0]);
    y = fptodp(vector[1]);
    z = fptodp(vector[2]);
    igStringObj_Format((igStringObj *)formatted.p, format, x, y, z, fptodp(vector[3]));
    text = (const char *)formatted.get()->name;
    if (text == 0) {
        text = g_stringObjEmptyText;
    }
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = (int)(StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = (int)(StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = StringPool_Intern(g_stringPool, text);
    }
    *result = interned;
    return 0;
}

bool igGetRegistryValue_Int(igRegistry *registry, int section, const char *key, int *out, int defaultValue, unsigned char create)
{
    return ((Gap::Core::igRegistry *)registry)->getValue(section, key, *out, defaultValue, create);
}

bool igGetRegistryValue_Float(igRegistry *registry, int section, const char *key, float *out, unsigned char create, float defaultValue)
{
    return ((Gap::Core::igRegistry *)registry)->getValue(section, key, *out, defaultValue, create);
}

bool igGetRegistryValue_StringObj(igRegistry *registry, int section, const char *key, igStringObj **out, const char *defaultValue, unsigned char create)
{
    return ((Gap::Core::igRegistry *)registry)->getValue(section, key, *(igStringObjRef *)out, defaultValue, create);
}

bool igGetRegistryValue_String(igRegistry *registry, int section, const char *key, char **out, char *def, unsigned char create)
{
    return ((Gap::Core::igRegistry *)registry)->getValue(section, key, *(igStringRef *)out, def, create);
}

bool igGetRegistryValue_Bool(igRegistry *registry, int section, const char *name, unsigned char *value, unsigned char defaultValue, unsigned char create)
{
    return ((Gap::Core::igRegistry *)registry)->getValue(section, name, *value, defaultValue, create);
}

int igGetRegistryValue_Vec3f(igRegistry *registry, int section, const char *key, float *value, const float *defaultValue, unsigned char create) {
    char *text;
    char *defaultText;
    int converted;

    text = 0;
    igConvertToString_Vec3f(&defaultText, defaultValue, "<%f,%f,%f>");
    if (((Gap::Core::igRegistry *)registry)->getValue(section, key, *(igStringRef *)&text, defaultText, create)) {
        converted = igConvertString_Vec3f(text, value, " < %f , %f , %f > ") & 0xFF;
        releaseString(defaultText);
        releaseString(text);
        return converted;
    }
    releaseString(defaultText);
    releaseString(text);
    return 0;
}

int igGetRegistryValue_Vec4f(igRegistry *registry, int section, const char *key, float *value, const float *defaultValue, unsigned char create) {
    char *text;
    char *defaultText;
    int converted;

    text = 0;
    igConvertToString_Vec4f(&defaultText, defaultValue, "<%f,%f,%f,%f>");
    if (((Gap::Core::igRegistry *)registry)->getValue(section, key, *(igStringRef *)&text, defaultText, create)) {
        converted = igConvertString_Vec4f(text, value, " < %f , %f , %f , %f > ") & 0xFF;
        releaseString(defaultText);
        releaseString(text);
        return converted;
    }
    releaseString(defaultText);
    releaseString(text);
    return 0;
}

