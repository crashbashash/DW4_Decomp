/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void FUN_0029de70(int, int, char *);
void FUN_0029c2a0(int, char *, int);
void FUN_0029c2a0(int p0, char * p1, int p2)
{
    FUN_0029de70(p0, *(int *)((char *)p0 + 8196), p1);
    EMPTY_MACRO();
}
