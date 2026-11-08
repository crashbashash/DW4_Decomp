/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void FUN_00267378(int);
void FUN_0026c6f8(char *);
void FUN_0026c6f8(char * p0)
{
    FUN_00267378(*(int *)((char *)p0 + 4));
    EMPTY_MACRO();
}
