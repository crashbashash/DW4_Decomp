typedef struct Wrapper { int pad; int inner; } Wrapper;
extern int FUN_0026aba8(int inner);
int FUN_00262900(Wrapper *w)
{
    if (w == 0)
        return 0;
    if (w->inner == 0)
        return 0;
    return FUN_0026aba8(w->inner);
}
