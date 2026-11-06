typedef struct Obj { char pad[8120]; char *sub; } Obj;
extern int FUN_002a96e0(Obj *);
extern void FUN_002a9628(char *);
extern int FUN_002abf68(void);
extern void FUN_00108f88(char *);
extern void FUN_00109118(void);
extern void FUN_002a9c50(Obj *);
void FUN_002a9bc8(Obj *o)
{
    char *sub;
    if (FUN_002a96e0(o)) {
        sub = o->sub;
        FUN_002a9628(sub + 4376);
        if (FUN_002abf68() != 1) {
            FUN_00108f88(sub + 4304);
        } else {
            FUN_00109118();
            FUN_002a9c50(o);
        }
    }
}
