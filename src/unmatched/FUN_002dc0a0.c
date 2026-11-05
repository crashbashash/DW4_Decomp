int FUN_002dc0a0(int arg0, int arg1, float fparg0, float fparg1) {
    switch (arg1) {
    case 0:
        if (fparg0 != fparg1) {
            return 0;
        }
        return 1;
    case 1:
        return fparg0 >= fparg1;
    case 2:
        if (fparg0 == fparg1) {
            return 0;
        }
        return 1;
    }
    return 0;
}
