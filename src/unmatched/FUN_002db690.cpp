extern "C" {
extern int DAT_004f9670[4];
int FUN_00129ef8(...);
int strlen(...);
int FUN_002db480(...);
int igStrCmp(...);
extern int DAT_004f9728[4];
bool FUN_002db690(char *arg0, int *arg1);
}
bool FUN_002db690(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s1;
    int var_s0;

    var_s1 = false;
    FUN_002db480();
    if (FUN_00129ef8(*(int *)(arg0 + 52), &DAT_004f9728[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        for (var_s0 = 0; var_s0 < 3; var_s0++) {
            if (igStrCmp(buf, DAT_004f9670[var_s0]) == 0) {
                *arg1 = var_s0;
                var_s1 = true;
                break;
            }
        }
    }
    return var_s1;
}
