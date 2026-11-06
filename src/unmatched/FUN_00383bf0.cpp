#include "dw4/reflected.h"
/* arg0 is the beFont: +36 _fonts (glyph list), +40 _fontIdx, +48 _lineFeedList, +52 _alignList. */
extern "C" {
typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
typedef struct IntList { char p0[8]; int count; int cap; int *data; } IntList;
typedef struct FloatList { char p0[8]; int count; int cap; float *data; } FloatList;
typedef struct Glyph { char p0[12]; float f12; } Glyph;
typedef struct GlyphList { char p0[16]; Glyph **data; } GlyphList;
typedef struct Mesh { char p0[12]; unsigned count; char *verts; int stride; } Mesh;
extern void List_Resize(void *, int, int);
void FUN_00383bf0(beFont *arg0, unsigned short *arg1, int arg2, Mesh *arg3);
}

void FUN_00383bf0(beFont *arg0, unsigned short *arg1, int arg2, Mesh *arg3) {
    float zo;
    unsigned short ch;
    int c;
    unsigned i;
    U u;
    int d;
    char *base;
    float *v;
    float yo;
    unsigned end;
    int a;
    unsigned n;
    IntList *li;
    float xo;
    int b;
    FloatList *lf;
    int sw;
    n = 0;
    xo = 0.0f;
    zo = 0.0f;
    ((IntList *)arg0->_lineFeedList)->count = 0;
    ((FloatList *)arg0->_alignList)->count = 0;
    ch = *arg1;
    base = arg3->verts;
    yo = xo;
    if (ch != 0) {
        do {
            sw = ch;
            switch (sw) {
            case 13:
                break;
            case 10:
                if (n != 0) {
                    li = ((IntList *)arg0->_lineFeedList);
                    a = li->count;
                    v = (float *)(base + arg3->stride * n);
                    if (a < li->cap) li->count = *(volatile int *)&li->count + 1; else List_Resize(li, a + 1, 4);
                    li->data[a] = n;
                    u.f = xo;
                    u.b.sign = 0;
                    lf = ((FloatList *)arg0->_alignList);
                    b = lf->count;
                    xo = *v - u.f;
                    if (b < lf->cap) lf->count = *(volatile int *)&lf->count + 1; else List_Resize(lf, b + 1, 4);
                    lf->data[b] = xo;
                    xo = -*v;
                    yo = yo - ((GlyphList *)arg0->_fonts)->data[arg0->_fontIdx]->f12;
                }
                break;
            default:
                end = n + 6;
                i = n;
                if (n < end) {
                  if (i < end) {
                    do {
                        v = (float *)(base + arg3->stride * i);
                        i++;
                        v[0] = v[0] + xo;
                        v[1] = v[1] + yo;
                        v[2] = v[2] + zo;
                    } while (i < end);
                  }
                }
                n += 6;
                break;
            }
            arg1++;
            ch = *arg1;
        } while (ch != 0);
    }
    arg3->count = n;
    li = ((IntList *)arg0->_lineFeedList);
    c = li->count;
    if (c < li->cap) li->count = *(volatile int *)&li->count + 1; else List_Resize(li, c + 1, 4);
    li->data[c] = n;
    lf = ((FloatList *)arg0->_alignList);
    d = lf->count;
    if (d < lf->cap) lf->count = *(volatile int *)&lf->count + 1; else List_Resize(lf, d + 1, 4);
    lf->data[d] = *v;
}
