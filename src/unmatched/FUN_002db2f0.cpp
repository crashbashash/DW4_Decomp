struct ConfigValueToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigValueResolver { char pad[20]; void *table; void *scope; int mode; };
extern "C" {
void *igObject_GetAllocator(void *);
ConfigValueToken *FUN_002b9500(void *);
void FUN_0030b320(ConfigValueToken *, char *, int);
int FUN_00306770(void *, void *, char *, ConfigValueToken **, char *, int);
int FUN_00306360(int, char *, int);
void igObject_Destroy(ConfigValueToken *);
extern char *DAT_004c22f0[4];
int FUN_002db2f0(ConfigValueResolver *self, ConfigValueToken *token, int key, int fallback);
}
static inline void releaseValue(ConfigValueToken *t) {
    if (t != 0) {
        t->_refCount = (int)t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
}
static inline char *textOf(ConfigValueToken *t) {
    char *s = t->text;
    s = (s == 0) ? DAT_004c22f0[0] : s;
    return s;
}
int FUN_002db2f0(ConfigValueResolver *self, ConfigValueToken *token, int key, int fallback) {
    ConfigValueToken *tmp;
    int result;
    if (token->kind == 0) {
        if (self->mode == 1) {
            return -1;
        }
        return fallback;
    }
    tmp = FUN_002b9500(igObject_GetAllocator(self));
    if (self->table == 0) {
        ConfigValueToken *held = tmp;
        char *s = token->text;
        int kind = token->kind;
        s = (s == 0) ? DAT_004c22f0[0] : s;
        FUN_0030b320(held, s, kind);
    } else {
        char *s = token->text;
        char *first = (s == 0) ? DAT_004c22f0[0] : s;
        s = (s == 0) ? DAT_004c22f0[0] : s;
        if ((FUN_00306770(self->table, self->scope, first, &tmp, s, 0) & 0xff) == 0 && self->mode == 1) {
            releaseValue(tmp);
            return -1;
        }
    }
    result = FUN_00306360(key, textOf(tmp), 1);
    releaseValue(tmp);
    return result;
}
