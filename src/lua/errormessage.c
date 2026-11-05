/* 0x00252f70 — 76 bytes. Wrapper: lua_tostring(self, 1); a null result defaults to
 * &DAT_004ebe58, then FUN_00125220(DAT_004854a0[0]->+0xc, &DAT_004ebe68, arg), 0.
 * The literal 1 is lua_tostring's second argument; the first is this function's a0. */
int *lua_tostring();
extern void * DAT_004854a0[4];
extern int DAT_004ebe58[4];
extern int DAT_004ebe68[4];
void FUN_00125220();

int errormessage(int self) {
    int *temp_v0;
    int *var_a2;

    temp_v0 = (int *)(lua_tostring(self, 1));
    var_a2 = (int *)(temp_v0);
    if (temp_v0 == 0) {
        var_a2 = (int *)(&DAT_004ebe58[0]);
    }
    FUN_00125220(*(int *)((char *)(DAT_004854a0[0]) + 12), &DAT_004ebe68[0], var_a2);
    return 0;
}
