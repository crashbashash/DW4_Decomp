/* 0x00236f30 — FUN_00236f30. hand-matched (member access keeps the base pointer, finding #509's
 * shape); verified byte-identical to retail by tools/verify.py. */
int FUN_002d7750();
int FUN_00457ca0();
extern int DAT_004fb410[4];
typedef struct Obj { char pad[28]; int f28; } Obj;

void FUN_00236f30(Obj *arg0, int arg1) {
    int sp2C;
    FUN_002d7750(&sp2C, arg0->f28, arg1);
    if (sp2C == DAT_004fb410[0]) {
        FUN_00457ca0(arg1, 0);
    }
}
