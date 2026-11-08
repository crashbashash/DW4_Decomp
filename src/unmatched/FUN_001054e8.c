void FUN_001067e8(int, int);
void FUN_001054e8(int, int);
void FUN_001054e8(int p0, int p1)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_001067e8(p0, 3);
    } while (0);
}
