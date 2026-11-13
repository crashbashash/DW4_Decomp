int strncmp(const char *, const char *, unsigned int);
int FUN_0027d568(char *);
void FUN_0027d678(char *chunk, int *info);

typedef struct {
    char *data;
    int size;
} ChunkArea;

char *SJ_SearchTag(ChunkArea *area, const char *tag, const char *stop, int *info)
{
    char *p;
    char *end;

    info[0] = 0;
    info[1] = 0;
    end = area->data + area->size;
    for (p = area->data; p < end; p += FUN_0027d568(p + 8) + 16) {
        if (strncmp(p, tag, 7) == 0) {
            FUN_0027d678(p, info);
            break;
        }
        if (stop != 0 && strncmp(p, stop, 7) == 0) {
            return 0;
        }
    }
    if (p < end) {
        return p;
    }
    return 0;
}
