/* 0x0020c7b0 — appends arg1 at the end of the singly linked chain starting at arg0 (next pointer at +32) and bumps the chain length byte at +71. Combat compiler at plain -O3. */
void FUN_0020c7b0(char *arg0, char *arg1) {
    char *p = arg0;
    while (*(char **)(p + 32) != 0) p = *(char **)(p + 32);
    *(char **)(p + 32) = arg1;
    *(int *)(arg1 + 32) = 0;
    arg0[71] = arg0[71] + 1;
}
