int memcmp(const void *a, const void *b, int size);
extern char D_005591a8[];
extern char D_00481e4c[];
extern char *D_00481f10;

int FUN_0010f268(void)
{
    char *expected = D_00481e4c;
    char *block = D_005591a8;
    int result = 0;
    if (memcmp(block, expected, 4) != 0
        && memcmp(block, D_00481f10, 4) != 0) {
        result = memcmp(expected, D_00481f10, 4) != 0;
    }
    return result;
}
