struct S { char p[44]; bool a; bool b; };
extern "C" int FUN_003a0540(S *s);
int FUN_003a0540(S *s) {
    return (s->a & !s->b) != 0;
}
