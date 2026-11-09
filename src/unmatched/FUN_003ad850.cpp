extern "C" {
extern int DAT_0058a810[8];
extern char GPR_005549dc;
int FUN_003ad7a0(int port, int slot);
int FUN_003ad850(int port, int onlyPresent);
}

int FUN_003ad850(int port, int onlyPresent) {
    int count;
    int i;
    count = 5;
    if (GPR_005549dc == -1)
        count = 2;
    else if (GPR_005549dc == 1)
        count = 5;
    for (i = 0; i < count; i++) {
        if (!onlyPresent || DAT_0058a810[i] == 1)
            FUN_003ad7a0(port, i);
    }
    for (i = count; i < 8; i++)
        DAT_0058a810[i] = 0;
    return count;
}
