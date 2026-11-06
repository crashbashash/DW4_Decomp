/* Validate two word arrays with a first-pass shortcut; result kept in a variable, early -1
 * returns; alternate compiler -O3. */
int FUN_001ea9c0(int);
int FUN_001eab60(int);
int FUN_00206540();
int FUN_001eaa50(int *arg0, int *arg1, int arg2, int arg3) {
    int ret;
    int i;
    ret = 1;
    for (i = 0; i < arg2; i++) {
        if (FUN_001eab60(arg0[i]) == 0) {
            break;
        }
    }
    if (i != arg2) {
        FUN_001ea9c0(1);
        FUN_00206540();
        ret = 0;
        for (i = 0; i < arg2; i++) {
            if (FUN_001eab60(arg0[i]) == 0) {
                return -1;
            }
        }
        for (i = 0; i < arg3; i++) {
            if (FUN_001eab60(arg1[i]) == 0) {
                return -1;
            }
        }
    }
    return ret;
}
