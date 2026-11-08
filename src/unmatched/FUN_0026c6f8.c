void FUN_00267378(int);
void FUN_0026c6f8(char *);
void FUN_0026c6f8(char * p0)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_00267378(*(int *)((char *)p0 + 4));
    } while (0);
}
