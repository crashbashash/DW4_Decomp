/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void FUN_002673d0(int);
void FUN_0026c718(char *);
void FUN_0026c718(char * p0)
{
    FUN_002673d0(*(int *)((char *)p0 + 4));
    EMPTY_MACRO();
}
