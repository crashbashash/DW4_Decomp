/* 0x00382eb0 - FUN_00382eb0. Two-pass conversion of a Shift-JIS string: pass one counts the characters found in a 425-entry code table (copied onto the stack) while streaming the raw bytes to a buffer object; pass two fills a pooled 16-bit string object, which is returned through a reference slot. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(void *);
struct Pair { unsigned short out; unsigned short key; };
struct Table { Pair e[425]; };
beUnicodeObj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
int strlen(const char *);
int FUN_0030b420(igStringObj *);
int FUN_0030b460(igStringObj *, char *, int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beFont *);
extern const Table DAT_004c8880;
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct Ref {
    beUnicodeObj *p;
    Ref(beUnicodeObj *x) { p = x; }
    ~Ref() { beUnicodeObj *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int FUN_00382eb0(Ref *out, beFont *self, const char *str) {
    Table t = DAT_004c8880;
    char c0;
    char c1;
    char c2;
    int n = 0;
    unsigned i = 0;
    int a;
    while (i < (unsigned)strlen(str)) {
        const char *p = str + i;
        unsigned c = (unsigned char)*p;
        if (c == 10) {
            if (n > 0) n++;
            i++;
        } else if (c == 13) {
            i++;
        } else if (c & 0x80) {
            unsigned short hi = (unsigned char)c << 8;
            unsigned short key = hi | (unsigned char)p[1];
            const char *sec = p + 1;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (key == q->key) { n++; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            FUN_0030b420((igStringObj *)self->_convertData);
            c0 = *p;
            FUN_0030b460((igStringObj *)self->_convertData, &c0, ((igStringObj *)self->_convertData)->_length, 1);
            c1 = *sec;
            FUN_0030b460((igStringObj *)self->_convertData, &c1, ((igStringObj *)self->_convertData)->_length, 1);
            i += 2;
        } else {
            unsigned char ch = c;
            unsigned short cc = ch;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (cc == q->key) { n++; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            FUN_0030b420((igStringObj *)self->_convertData);
            c2 = *p;
            FUN_0030b460((igStringObj *)self->_convertData, &c2, ((igStringObj *)self->_convertData)->_length, 1);
            i++;
        }
    }
    a = igObject_GetAllocator(self);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    Ref r(FUN_003614f0(a));
    beUnicodeObj_AllocateBuffer(r.p, n);
    unsigned short *buf = (unsigned short *)r.p->_buffer;
    int m = 0;
    unsigned j = 0;
    while (j < (unsigned)strlen(str)) {
        const char *p = str + j;
        unsigned c = (unsigned char)*p;
        if (c == 10) {
            if (m > 1) buf[m++] = c;
            j++;
        } else if (c == 13) {
            j++;
        } else if (c & 0x80) {
            unsigned short hi = (unsigned char)c << 8;
            unsigned short key = hi | (unsigned char)p[1];
            int k = 0;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (key == q->key) { buf[m++] = t.e[k].out; break; }
                    q++;
                    k++;
                } while (q->out != 0xffff);
            }
            j += 2;
        } else {
            unsigned char ch = c;
            unsigned short cc = ch;
            Pair *q = t.e;
            if (q->out != 0xffff) {
                do {
                    if (cc == q->key) { buf[m++] = ch; break; }
                    q++;
                } while (q->out != 0xffff);
            }
            j++;
        }
    }
    buf[m] = 0;
    out->p = r.p;
    if (out->p) ++out->p->_refCount;
    return 0;
}
