struct s { int a; int b; };
void FUN_00285a58(char *arg0, int arg1, int arg2) {
    struct s *p = (struct s *)(arg0 + 0x148);
    p->a = arg1;
    p->b = arg2;
}
