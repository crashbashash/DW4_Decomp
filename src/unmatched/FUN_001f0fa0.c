union H { struct { short a; char b; } s; int i; };
union T { short s; int i; };
extern union H DAT_00490e20[4];
extern union T DAT_00490e30[4];
extern int DAT_00490e34[4];
extern int DAT_00490e38[4];
extern int DAT_00490e3c[4];
extern short DAT_0049149a[8];
extern int DAT_004e50f8[4];
typedef struct Packet { char *cursor; } Packet;
static inline char *position(const Packet *packet) { return packet->cursor; }
void FUN_001f0fa0(unsigned int arg0, int arg1, int arg2, Packet *arg3) {
    char *base;
    char *src;
    char *p;
    unsigned int i;
    int d;
    char *cur;
    base = arg3->cursor;
    src = (char *)(arg1 + arg2);
    i = 0;
    arg3->cursor = base + 16;
    DAT_00490e20[0].s.b = arg0;
    DAT_00490e20[0].s.a = DAT_0049149a[0] | 0xC000;
    p = arg3->cursor;
    arg3->cursor = p + 4;
    *(int *)p = DAT_00490e20[0].i;
    for (; i < arg0; i++) {
        *arg3->cursor++ = *src++;
    }
    while ((int)arg3->cursor & 3) {
        *arg3->cursor++ = 0;
    }
    while ((int)(cur = position(arg3)) & 0xF) {
        p = arg3->cursor;
        arg3->cursor = p + 4;
        *(int *)p = DAT_004e50f8[0];
    }
    d = (cur - base) / 16;
    DAT_00490e30[0].s = d - 1;
    *(int *)base = DAT_00490e30[0].i;
    *(int *)(base + 4) = DAT_00490e34[0];
    *(int *)(base + 8) = DAT_00490e38[0];
    *(int *)(base + 12) = DAT_00490e3c[0];
}
