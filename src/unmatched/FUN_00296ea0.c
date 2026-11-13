int FUN_002968c0(void *ply);
int FUN_00295e10(void *ply);
int FUN_00299c80(void *obj);
void mwsfd_Error(const char *message);

extern char DAT_004f3e08[];

int FUN_00296ea0(char *ply) {
    int a, b, result;

    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f3e08);
        return 0;
    }
    a = FUN_00295e10(ply);
    b = FUN_00299c80(ply + 660);
    if (a == b) {
        result = a;
    } else if (a != 0) {
        result = a;
    } else {
        result = b;
    }
    return result;
}
