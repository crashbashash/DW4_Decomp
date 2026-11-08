int FUN_00290898(void *strm);
int FUN_00290ac0(void *strm, int flag, int arg);

int FUN_002909f0(char *obj, int mask, void *strm) {
    int *stat = (int *)(obj + 592);
    int has = *(int *)(obj + 404);
    int result;
    int type;

    if (*(int *)(obj + 896) != 0) {
        *(int *)(obj + 896) = 0;
        *(int *)(obj + 900) += 1;
        stat[3] += 1;
        if (has == 0) {
            return -2;
        }
        stat[4] += 1;
    }
    result = (has == 0) ? -2 : -3;
    do {
        type = FUN_00290898(strm);
        if (type == 0) {
            break;
        }
        if (type & mask) {
            result = 0;
            break;
        }
    } while (FUN_00290ac0(strm, 1, 4) == 4);
    return result;
}
