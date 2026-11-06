/* The limit is compared as `> 0x7FF` so the slti result stays in at. */
int FUN_0012fde0();
int FUN_0030b320();

int FUN_0030b840(int arg0) {
    int buf[512];
    int var_s0;

    var_s0 = FUN_0012fde0(buf);
    if (var_s0 > 0x7FF) {
        var_s0 = -1;
    } else {
        FUN_0030b320(arg0, buf, var_s0);
    }
    return var_s0;
}
