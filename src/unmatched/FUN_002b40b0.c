typedef struct Pair { int a; int b; } Pair;
void FUN_002b40b0(char *arg0, int arg1, int arg2)
{
    Pair *p = (Pair *)(arg0 + 96);
    p->a = arg1;
    p->b = arg2;
}
