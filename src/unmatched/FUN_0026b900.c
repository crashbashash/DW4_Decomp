extern char adxt_obj[];
int ADXT_Destroy();

void FUN_0026b900(void) {
    int var_s1;
    char *var_s0;

    var_s0 = (char *)adxt_obj;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            ADXT_Destroy(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0xC4;
    } while (var_s1 >= 0);
}
