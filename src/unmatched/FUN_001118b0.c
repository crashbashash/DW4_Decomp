void FUN_001103e8(int, int);
void FUN_001118b0(int, int);
void FUN_001118b0(int p0, int p1)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_001103e8(p0, 21);
    } while (0);
}
