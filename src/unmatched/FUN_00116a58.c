void FUN_00116740(int, int, int);
void FUN_00116a58(int, int, int);
void FUN_00116a58(int p0, int p1, int p2)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_00116740(p0, p1, 0);
    } while (0);
}
