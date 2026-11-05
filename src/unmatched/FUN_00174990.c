int FUN_001edcc0();

void FUN_00174990(void *arg0, int arg1, int arg2, int arg3, int arg4) {
    *(char *)((char *)(arg0) + 1252) = arg1;
    *(char *)((char *)(arg0) + 1253) = arg2;
    *(char *)((char *)(arg0) + 1254) = arg3;
    *(char *)((char *)(arg0) + 1255) = arg4;
    FUN_001edcc0(arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, arg4 & 0xFF);
}
