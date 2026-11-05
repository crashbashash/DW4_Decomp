void FUN_00465e40(void *arg0, int arg1, char arg2) {
    switch (arg1) {
    case 0:
        *(char *)((char *)(arg0) + 88) = arg2;
        break;
    case 2:
        *(char *)((char *)(arg0) + 89) = arg2;
        break;
    case 1:
        *(char *)((char *)(arg0) + 90) = arg2;
        break;
    }
    *(int *)((char *)(arg0) + 112) = 0;
}
