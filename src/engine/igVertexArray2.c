#include "dw4/typecast.h"
extern int DAT_0055fa58[4];
struct S { char p0[8]; int count; char p12[4]; int **items; };
typedef struct L { int p0,p4; int n; int p12; int *data; } L;
typedef struct VL { char p[8]; int n; int pad; int *data; } VL;
typedef struct A { char p[16]; VL *l; } A;
typedef struct O { char p[16]; int k0; int k1; } O;

static int FUN_0015f430(void *arg0, int arg1, int arg2, int arg3) { if (arg1 == *(int *)((char *)(arg0) + 16)) { if (arg2 == *(int *)((char *)(arg0) + 20)) { return 1; } } return 0; }

static int FUN_0015f460(void *arg0, int arg1, int arg2, int arg3)
{
  if (arg1 == (*((int *) (((char *) arg0) + 16))))
  {
    if ((arg3 == (*((int *) (((char *) arg0) + 28)))) && (arg2 == (*((int *) (((char *) arg0) + 20)))))
    {
      return 1;
      return 0;
    }
  }
  return 0;
}

int *FUN_0015f4a0(struct S *s, int a1, int a2) {
    int *found = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        int *item = s->items[i];
        if (FUN_0015f430(item, a1, a2, 0) != 0) { found = item; break; }
    }
    return found;
}

void *FUN_0015f510(L *l, int a1, int a2, int a3) {
  void *r = 0; int i; void *e;
  for (i = 0; i < l->n; i++) { e = (void*)l->data[i]; if (FUN_0015f460(e, a1, a3, a2)) { r = e; break; } }
  return r; }

void *igVertexArray2__FindVertexData(A *arg0, int arg1, int arg2) {
    void *res;
    int i;
    O *o;
    int n;
    res = 0;
    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        o = (O *)dw4_cast_or_null((char *)arg0->l->data[i], DAT_0055fa58);
        if (arg1 == o->k0 && arg2 == o->k1) {
            res = o;
            break;
        }
    }
    return res;
}
