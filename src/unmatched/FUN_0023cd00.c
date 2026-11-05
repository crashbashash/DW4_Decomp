/* 0x0023cd00 — FUN_0023cd00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0023cd00(char *arg0) {
    char temp_v0;

    temp_v0 = *arg0;
    switch (temp_v0) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 11:
    case 12:
        return 1;
    default:
        return 0;
    }
}
