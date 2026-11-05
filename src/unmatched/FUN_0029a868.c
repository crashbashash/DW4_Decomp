/* Dispatches on the mode at +8 (1 -> FUN_0029a4b8, 2 -> FUN_0029a7d8; 0, 3, 4 do nothing), then always runs FUN_0029a8e0 and FUN_00296320. Returns 0. */
typedef struct Obj { char pad[8]; unsigned int mode; } Obj;
extern void FUN_0029a4b8(Obj *);
extern void FUN_0029a7d8(Obj *);
extern void FUN_0029a8e0(Obj *);
extern void FUN_00296320(Obj *);
int FUN_0029a868(Obj *o)
{
    switch (o->mode) {
    case 1:
        FUN_0029a4b8(o);
        break;
    case 2:
        FUN_0029a7d8(o);
        break;
    case 0:
    case 3:
    case 4:
    default:
        break;
    }
    FUN_0029a8e0(o);
    FUN_00296320(o);
    return 0;
}
