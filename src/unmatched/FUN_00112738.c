int memcmp(const void *a, const void *b, int size);
extern char D_00559668[];
extern char D_00481e4c[];
extern char *D_00481f24;

int FUN_00112738(void)
{
    char *expected = D_00481e4c;
    char *block = D_00559668;
    int result = 0;
    if (memcmp(block, expected, 4) != 0
        && memcmp(block, D_00481f24, 4) != 0) {
        result = memcmp(expected, D_00481f24, 4) != 0;
    }
    return result;
}
