int FUN_002d7e90();
int FUN_002d86b0();
int igNamedObject_SetName();
int igObject_VisitFields();
extern int DAT_00586730[4];
int FUN_002d8520();

int FUN_002d8620(int arg0, int arg1, int arg2) {
    int temp_v0;

    if (arg1 != 0) {
        igObject_VisitFields(arg1, &FUN_002d8520, arg0);
        temp_v0 = FUN_002d86b0(arg0, DAT_00586730[0], arg1);
        igNamedObject_SetName(FUN_002d7e90(arg0, temp_v0), arg2);
        return temp_v0;
    }
    return -1;
}
