int sprintf(char *buf, const char *fmt, ...);
void FUN_0026d7a0(void *handle, const char *path);

extern char DAT_004ee4a0[];

void FUN_0026aee0(void *handle, int sector, unsigned int size)
{
    char path[32];

    sprintf(path, DAT_004ee4a0, sector, (size + 2047) / 2048);
    FUN_0026d7a0(handle, path);
}
