int sprintf(char *buf, const char *format, ...);
void *FUN_002eb010(int size);
void *StringPool_Construct(void *pool);
int StringPool_Intern(void *pool, const char *text);
extern char DAT_004e0dc8[];
extern void *DAT_00586f20[4];

static inline int internString(const char *text) {
    if (text == 0) {
        return 0;
    }
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    return StringPool_Intern(DAT_00586f20[0], text);
}

void Gap__igVec4fMetaField__vfunc_57(int *out, void *field, const float *value) {
    char text[1024];
    sprintf(text, DAT_004e0dc8, value[0], value[1], value[2], value[3]);
    *out = internString(text);
}
