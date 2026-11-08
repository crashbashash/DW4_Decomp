void FUN_0029de70(int, int, char *);
void FUN_0029c2a0(int, char *, int);
void FUN_0029c2a0(int p0, char * p1, int p2)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_0029de70(p0, *(int *)((char *)p0 + 8196), p1);
    } while (0);
}
