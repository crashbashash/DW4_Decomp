extern "C" {
void igProperty_FindByName(int, int, char *);
void FUN_003a92e0(int, char *, int);
}
void FUN_003a92e0(int p0, char * p1, int p2)
{
    igProperty_FindByName(p0, *(int *)0x00585be0, p1);
}
