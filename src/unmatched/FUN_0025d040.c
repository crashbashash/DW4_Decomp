extern int (*adxkey_cbfunc)(int, int);
extern int adxkey_cbobj[4];
int FUN_0025d040(int arg0) {
    if (adxkey_cbfunc != 0) {
        adxkey_cbfunc(adxkey_cbobj[0], arg0);
    }
    return 0;
}
