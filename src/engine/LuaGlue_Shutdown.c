int FUN_0023f6a0();
int FUN_0023f9b0();
int FUN_0023fcc0();
int FUN_0023fe50();
int FUN_00241790();
int FUN_002444c0();
int FUN_00244550();
int FUN_00244560();
int FUN_002445d0();
int FUN_00244640();
int FUN_00244650();
int igObject_Destroy();
typedef struct R { int w0; int rc; } R;
extern R * DAT_0056de30[4];
extern R * DAT_0056de38[4];
void LuaGlue_Shutdown(void) {
    int sp20[4];
    R *t;
    int temp_s0;

    FUN_0023fe50();
    FUN_0023fcc0();
    FUN_0023f9b0();
    FUN_0023f6a0();
    FUN_00241790();
    t = DAT_0056de38[0];
    t->rc = t->rc - 1;
    if ((t->rc & 0x7FFFFF) == 0) {
        igObject_Destroy(t);
    }
    FUN_00244650(sp20);
    while (FUN_00244550(sp20) != 0) {
        temp_s0 = FUN_00244640(sp20);
        FUN_002445d0(sp20, 0);
        FUN_00244560(temp_s0, 1);
    }
    FUN_002444c0(sp20, -1);
    t = DAT_0056de30[0];
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
}
