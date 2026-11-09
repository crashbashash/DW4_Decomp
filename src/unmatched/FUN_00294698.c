typedef struct PicLogItem {
    int w[4];
} PicLogItem;

typedef struct PicLogEntry {
    int used;
    int frame;
    int a;
    int b;
    int c;
} PicLogEntry;

typedef struct PicLogLog {
    char pad[184];
    int count;
    int f188;
    int idx;
    PicLogEntry entry[8];
} PicLogLog;

int FUN_00294360(PicLogItem *h);
int FUN_002944f0(PicLogItem *h);
int FUN_002947d0(PicLogItem *h);
PicLogItem *FUN_002b17d8(char *buf, int size);
void FUN_002b18a0(PicLogItem *h);
int FUN_002b19f0(PicLogItem *h, int *out);

void FUN_00294698(PicLogLog *log, char *buf, unsigned int size)
{
    PicLogItem *h;
    int v[2];
    int a, b, c;
    int i;

    log->count++;
    if (size < 2048 || buf == 0)
        return;
    h = FUN_002b17d8(buf, size);
    if (h == 0)
        return;
    if (FUN_002b19f0(h, v) == 0 || v[0] == 0) {
        FUN_002b18a0(h);
        return;
    }
    a = FUN_002947d0(h);
    b = FUN_00294360(h);
    c = FUN_002944f0(h);
    i = log->idx;
    log->entry[i].frame = log->count - 1;
    log->entry[i].a = a;
    log->entry[i].b = b;
    log->entry[i].c = c;
    log->entry[i].used = 1;
    log->idx = (log->idx + 1) % 8;
    FUN_002b18a0(h);
}
