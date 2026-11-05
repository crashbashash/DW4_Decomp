struct T { int pad[8]; int cnt; };
struct S { char pad[8052]; struct T *p; };
int FUN_002a22b8(struct S *arg0) {
    struct T *t = arg0->p;
    return t->cnt = t->cnt + 1;
}
