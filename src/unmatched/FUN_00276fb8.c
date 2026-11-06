int FUN_00277278();
int memset();

void FUN_00276fb8(char *arg0) {
    if (arg0 != 0) {
        FUN_00277278();
        *arg0 = 0;
        memset(arg0, 0, 0x238);
    }
}
