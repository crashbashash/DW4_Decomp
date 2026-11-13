/* mwl_convPtypeToSFD (named by its diagnostic string): passes picture types 1..4 through; anything
 * else is reported as "Invalid Ptype" and treated as 1. */
void mwsfd_Error(const char *message);

extern char DAT_004f31b0[]; /* "mwl_convPtypeToSFD : Invalid Ptype" */

int FUN_002940a0(unsigned int type) {
    int result;

    switch (type) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
        result = 4;
        break;
    default:
        mwsfd_Error(DAT_004f31b0);
        result = 1;
        break;
    }
    return result;
}
