void *memset(void *dst, int value, unsigned int size);
void FUN_00276220(const char *name, char *path);
void FUN_002725a0(int mark);
int FUN_002728b0(char *path, int mode);
long long FUN_00272780(int fd, long long offset, int whence);
int FUN_00272970(int fd, void *buf, int size);
int FUN_00272918(int fd);

int FUN_002765e0(const char *name, void *buf)
{
    char path[256];
    int fd;
    long long size;
    int ret;

    memset(path, 0, 256);
    FUN_00276220(name, path);
    FUN_002725a0(0x6000);
    fd = FUN_002728b0(path, 1);
    FUN_002725a0(0x6001);
    if (fd < 0) {
        return 0;
    }
    FUN_002725a0(0x6100);
    size = FUN_00272780(fd, 0, 2);
    FUN_002725a0(0x6101);
    if (size < 0) {
        return 0;
    }
    FUN_002725a0(0x6200);
    ret = FUN_00272780(fd, 0, 0);
    FUN_002725a0(0x6201);
    if (ret < 0) {
        return 0;
    }
    if (size > 4096) {
        size = 4096;
    }
    FUN_002725a0(0x6300);
    ret = FUN_00272970(fd, buf, size);
    FUN_002725a0(0x6301);
    if (ret < 0) {
        FUN_002725a0(0x6500);
        FUN_00272918(fd);
        FUN_002725a0(0x6501);
        return 0;
    }
    FUN_002725a0(0x6400);
    FUN_00272918(fd);
    FUN_002725a0(0x6401);
    return 1;
}
