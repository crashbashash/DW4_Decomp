/* Repeats FUN_002a3cb8 then FUN_002a4468 while the latter asks for more and both succeed, then
 * runs FUN_002a75b8; returns the first error. */
int FUN_002a3cb8();
int FUN_002a4468();
void FUN_002a75b8();

int FUN_002a3c38(void *player) {
    int a;
    int b;
    int c;
    int more;
    int status;

    do {
        status = FUN_002a3cb8(player, &a, &b, &c);
        if (status != 0) {
            break;
        }
        status = FUN_002a4468(player, a, b, c, &more);
        if (status != 0) {
            break;
        }
    } while (more != 0);
    FUN_002a75b8(player);
    return status;
}
