typedef struct Obj { char pad[464]; int f464; int f468; } Obj;
extern void FUN_00295808(void);
extern void FUN_002954c8(Obj *);
extern void FUN_00295be0(Obj *, int);
extern void FUN_00296310(Obj *, int, int);
extern void FUN_00296318(Obj *, int, int);
void FUN_00295658(Obj *o, int a, int b, int c)
{
    o->f464 = o->f468;
    FUN_00295808();
    FUN_002954c8(o);
    FUN_00295be0(o, a);
    FUN_00296310(o, b, c);
    FUN_00296318(o, b, c);
}
