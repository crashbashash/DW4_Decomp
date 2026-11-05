int FUN_0032ac70(int arg0, unsigned int arg1) {
    return (((unsigned int *)arg0)[arg1 >> 4] >> ((arg1 & 0xF) * 2)) & 3;
}
