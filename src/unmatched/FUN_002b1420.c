/* When FUN_002adc40(obj, 5) is set, runs FUN_002b1478, FUN_002b15c8 and FUN_002b1540 on obj and
 * returns FUN_002b15c8's result; otherwise returns 0. */
int FUN_002adc40();
int FUN_002b1478();
int FUN_002b1540();
int FUN_002b15c8();

int FUN_002b1420(int obj) {
    int result;

    if (FUN_002adc40(obj, 5) == 0) {
        return 0;
    }
    FUN_002b1478(obj);
    result = FUN_002b15c8(obj);
    FUN_002b1540(obj);
    return result;
}
