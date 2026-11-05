int FUN_00320f70(void *arg0, int arg1) {
    char *base = *(char **)((char *)arg0 + 96);
    if (base != 0 && arg1 >= 0 && arg1 <= *(int *)((char *)arg0 + 92)) return (int)(base + arg1*16); return 0;
}
