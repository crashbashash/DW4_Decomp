/* 0x001ad5c0 - FUN_001ad5c0. Sorted insert of an object into slot arg2 of a list of priority-ordered object lists: finds the first element with a higher priority, appends or inserts (retained through a volatile stack slot, which retail re-reads), then bumps or clamps the per-slot index in the index list with the bounds-checked store idiom; one index-list pointer per section (separate webs), the next index is computed before the test; alternate compiler -O3. */
typedef struct IL { int p0, p1; int count; int cap; int *data; } IL;
typedef struct X { char p0[12]; int w12; } X;
typedef struct It { int p0; int refs; char p8[4]; X *x; char p16[32]; int prio; } It;
typedef struct Ls { int p0, p1; int count; int cap; It **data; } Ls;
typedef struct LL { int p0, p1; int count; int cap; Ls **data; } LL;
typedef struct A { char p0[48]; LL *ll; IL *il; char p56[24]; char b80; } A;
int List_InsertWords();
int ObjectList_AppendRetained();
void FUN_001ad5c0(A *arg0, It *arg1, int arg2) {
    Ls *l;
    It *volatile sp6C;
    int n, i, v, nv;
    It *e;
    IL *il, *il2, *il3;
    int *p;
    l = arg0->ll->data[arg2];
    n = l->count;
    if (n == 0) {
        ObjectList_AppendRetained(l, arg1);
        il = arg0->il;
        if (il->count != 0 && arg2 >= 0 && arg2 < il->count) {
            il->data[arg2] = 0;
        }
        arg0->b80 = 0;
        return;
    }
    i = 0;
    do {
        e = l->data[i];
        if (e->prio > arg1->prio) break;
        i++;
    } while (i != n);
    if (i == n) {
        ObjectList_AppendRetained(l, arg1);
    } else {
        It *t;
        sp6C = arg1;
        t = sp6C;
        if (t != 0) {
            t->refs += 1;
        }
        List_InsertWords(l, i, 1, (It **)&sp6C);
        il2 = arg0->il;
        p = &il2->data[arg2];
        v = *p;
        nv = v + 1;
        if (i <= v) {
            if (il2->count != 0 && arg2 >= 0 && arg2 < il2->count) {
                *p = nv;
            }
            arg0->b80 = 0;
        }
    }
    if (arg1->x->w12 == 0) {
        il3 = arg0->il;
        p = &il3->data[arg2];
        if (*p < i) {
            if (il3->count != 0 && arg2 >= 0 && arg2 < il3->count) {
                *p = i;
            }
            arg0->b80 = 0;
        }
    }
}
