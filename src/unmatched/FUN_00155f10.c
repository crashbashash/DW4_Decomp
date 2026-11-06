/* Finds the index of the list entry (list at +304) whose +20 field equals an interned string
 * obtained from a helper; each entry is held through a volatile stack slot (retail stores and re-
 * reads it) and released with the inlined null-checked reference-count decrement and destroy; the
 * string is released on every exit; returns -1 when absent; alternate compiler -O3. */
typedef struct Obj { int w0; unsigned refs; char p8[12]; int w20; } Obj;
typedef struct Lst { int p0, p1; int count; int cap; Obj **data; } Lst;
typedef struct S { char p0[304]; Lst *list; } S;
int FUN_001554a0();
void StringChunk_ReleaseHeader();
int igObject_Destroy();
int FUN_00155f10(S *arg0) {
    char *sp3C;
    Obj *volatile sp38;
    Obj *o;
    int s0;
    FUN_001554a0(&sp3C);
    s0 = 0;
    if (arg0->list->count > 0) {
        goto test;
    body:
        sp38 = arg0->list->data[s0];
        o = sp38;
        if (o != 0) {
            o->refs += 1;
        }
        o = sp38;
        if (o == 0) {
            if (o != 0) {
                o->refs -= 1;
                if ((o->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
            goto next;
        }
        if (o->w20 == (int)sp3C) {
            if (o != 0) {
                o->refs -= 1;
                if ((o->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
            if (sp3C != 0) {
                int *h = (int *)sp3C - 2;
                int c = h[1] - 1;
                h[1] = c;
                if (c == 0) {
                    StringChunk_ReleaseHeader(h[0], h);
                }
            }
            return s0;
        }
        if (o != 0) {
            o->refs -= 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    next:
        s0 += 1;
    test:
        if (s0 < arg0->list->count) goto body;
    }
    if (sp3C != 0) {
        int *h = (int *)sp3C - 2;
        int c = h[1] - 1;
        h[1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(h[0], h);
        }
    }
    return -1;
}
