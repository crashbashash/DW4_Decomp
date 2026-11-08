void _sceSifLoadElfPart(int, int, int, int);
void FUN_00113180(int, int, int, int);
void FUN_00113180(int p0, int p1, int p2, int p3)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        _sceSifLoadElfPart(p0, p1, p2, 1);
    } while (0);
}
