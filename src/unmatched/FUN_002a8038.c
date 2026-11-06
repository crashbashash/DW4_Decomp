/* Runs FUN_002a8088 under the FUN_002a0e70/FUN_002a0e88 guard and returns its result. */
void FUN_002a0e70();
void FUN_002a0e88();
int FUN_002a8088();

int FUN_002a8038(void *player, int arg) {
    char guard[16];
    int result;

    FUN_002a0e70(guard);
    result = FUN_002a8088(player, arg);
    FUN_002a0e88(guard);
    return result;
}
