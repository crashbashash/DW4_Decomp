int FUN_00300600();
int FUN_003006a0();
int FUN_00300770();

void FUN_00300c00(int arg0, int arg1, int arg2) {
    switch (arg2) {
    case 1:
        FUN_003006a0();
        break;
    case 0:
        FUN_00300770();
        break;
    case 2:
        FUN_00300600();
        break;
    }
}
