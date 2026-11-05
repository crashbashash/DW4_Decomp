/* Forwards to FUN_0026aba8 with the inner object, or yields 0 when the
 * wrapper or its inner object is absent. */
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
