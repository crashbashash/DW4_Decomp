int FUN_0018a660(int);
int FUN_001b2f30(int, int, int);
int igObject_GetAllocator(int);

int FUN_001b2ed0(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = FUN_0018a660(igObject_GetAllocator(arg1));
    FUN_001b2f30(arg0, arg1, temp_v0);
    return temp_v0;
}
