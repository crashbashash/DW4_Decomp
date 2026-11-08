int sceIpuStopDMA();
int FUN_0010a418(int arg0) {
    arg0 = *(int *)(arg0 + 64);
    sceIpuStopDMA(arg0 + 0x68);
    return 1;
}
