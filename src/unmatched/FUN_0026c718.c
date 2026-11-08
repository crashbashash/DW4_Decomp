void FUN_002673d0(int);
void FUN_0026c718(char *);
void FUN_0026c718(char * p0)
{
    /* matching construct: hand search — inside the loop the call is not a tail call, so the frame stays */
    do {
        FUN_002673d0(*(int *)((char *)p0 + 4));
    } while (0);
}
