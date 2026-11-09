int memset();
void *memcpy(void *, const void *, unsigned int);
int strcmp();
extern char DAT_004f08e8[];

int FUN_002761c8(char *tag)
{
    char buf[6];

    memset(buf, 0, 6);
    memcpy(buf, tag, 4);
    buf[5] = 0;
    return strcmp(buf, DAT_004f08e8) == 0;
}
