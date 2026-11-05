void FUN_003374e0(int *arg0, int arg1, unsigned long long arg2) {
    arg0[0] = (int)(arg2 & 0xFFFFFFFF); arg0[1] = (int)(arg2 >> 32);
    arg0[2] = arg1;
    arg0[3] = 0;
}
