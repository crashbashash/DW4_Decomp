int sprintf(char *buf, const char *fmt, ...);
void *FUN_002eb010(int size);
void *StringPool_Construct(void *pool);
char *StringPool_Intern(void *pool, const char *s);

extern char DAT_004e0db8[];
extern void *g_stringPool;

void Gap__igVec3fMetaField__vfunc_57(char **out, int unused, float *v)
{
    char buf[1024];
    char *s;
    void *pool;

    sprintf(buf, DAT_004e0db8, v[0], v[1], v[2]);
    if (buf == 0) {
        s = 0;
    } else {
        if (g_stringPool == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0)
                pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        s = StringPool_Intern(g_stringPool, buf);
    }
    *out = s;
}
