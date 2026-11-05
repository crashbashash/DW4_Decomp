struct L { int pad[2]; int count; int cap; int *data; };
struct O { int pad[4]; struct L *l; };

int *FUN_002d3b80(struct O *o, int i) {
int *r; if (i < 0 || i >= o->l->count || o->l->data == 0) { r = 0; } else { r = o->l->data + i; if (i > 0 && r[-1] != 0) r = 0; } return r;
}
