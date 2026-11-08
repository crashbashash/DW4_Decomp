void _sceSifLoadModule(int, int, int, int, int);
void FUN_00113058(int, int, int, int, int);
void FUN_00113058(int p0, int p1, int p2, int p3, int p4)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        _sceSifLoadModule(p0, p1, p2, p3, 0);
    } while (0);
}
