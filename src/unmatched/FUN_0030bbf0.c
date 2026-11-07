void *FUN_002b9500();
int FUN_0030b3c0();
int FUN_0030b460();
int igObject_Destroy();
int igObject_GetAllocator();
extern char *DAT_004c22f0[4];
typedef struct Str { char pad[4]; int _refCount; char *text; unsigned int length; } Str;
static inline char *text(Str *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
int FUN_0030bbf0(Str *self, unsigned int pos, unsigned int len) {
    unsigned int end;
    Str *tmp;
    Str *held;

    if (pos > self->length - 1 || (end = pos + len) > self->length) {
        return 0;
    }
    *(Str *volatile *)&tmp = FUN_002b9500(igObject_GetAllocator(self));
    FUN_0030b3c0(tmp, self->text + end);
    FUN_0030b460(tmp, self->text, 0, pos);
    FUN_0030b3c0(self, text(tmp));
    held = tmp;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
    return 1;
}
