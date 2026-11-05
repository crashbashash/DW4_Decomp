#include "dw4/ipa/ipa_FUN_0015f460.h"
typedef struct L { int p0,p4; int n; int p12; int *data; } L;
void *FUN_0015f510(L *l, int a1, int a2, int a3) {
  void *r = 0; int i; void *e;
  for (i = 0; i < l->n; i++) { e = (void*)l->data[i]; if (FUN_0015f460(e, a1, a3, a2)) { r = e; break; } }
  return r; }
