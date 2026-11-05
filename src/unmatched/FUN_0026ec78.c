/* CRI ADXT handle: when the handle has an attached object (+8) and passes the
 * FUN_0026bd20 check, dispatch on the signed byte at +2 (jump table at
 * 0x4eee40, five entries): kinds 0 and 1 forward the stream (+4) only when
 * the +8 object reports 3, kind 2 forwards it unconditionally, 3 and 4 do
 * nothing. */
typedef struct Adxt {
    char used;
    signed char state;
    signed char kind;
    char pad;
    int stm;
    int obj;
} Adxt;

extern int FUN_0026bd20(Adxt *adxt);
extern int FUN_0026a138(int obj);
extern void FUN_00266268(int stm);

void FUN_0026ec78(Adxt *adxt)
{
    if (adxt->obj == 0)
        return;
    if (FUN_0026bd20(adxt) == 0)
        return;
    switch (adxt->kind) {
    case 0:
    case 1:
        if (FUN_0026a138(adxt->obj) == 3)
            FUN_00266268(adxt->stm);
        break;
    case 2:
        FUN_00266268(adxt->stm);
        break;
    case 3:
    case 4:
        break;
    }
}
