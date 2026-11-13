typedef struct Obj { char pad[8]; unsigned int mode; } Obj;
extern void mwply_UpdateStat(Obj *);
extern void FUN_0029a7d8(Obj *);
extern void FUN_0029a8e0(Obj *);
extern void FUN_00296320(Obj *);
int FUN_0029a868(Obj *o)
{
    switch (o->mode) {
    case 1:
        mwply_UpdateStat(o);
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
