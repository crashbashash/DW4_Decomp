/* afs.c — CRI AFS archive reader.  See dw4/afs.h. */
#include "dw4/afs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

static uint32_t rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

int dw4_afs_is_archive(const uint8_t *buf, size_t len)
{
    return len >= 8 && buf[0] == 'A' && buf[1] == 'F' && buf[2] == 'S' && buf[3] == 0;
}

static int read_all(const char *path, uint8_t **out, size_t *out_len)
{
    FILE *f = fopen(path, "rb");
    long n;
    uint8_t *buf;

    if (!f)
        return -1;
    if (fseek(f, 0, SEEK_END) != 0 || (n = ftell(f)) < 0 || fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return -1;
    }
    buf = (uint8_t *)malloc((size_t)n ? (size_t)n : 1);
    if (!buf) {
        fclose(f);
        return -1;
    }
    if (n && fread(buf, 1, (size_t)n, f) != (size_t)n) {
        free(buf);
        fclose(f);
        return -1;
    }
    fclose(f);
    *out = buf;
    *out_len = (size_t)n;
    return 0;
}

static int parse_table(dw4_afs *a)
{
    uint32_t i;

    if (!dw4_afs_is_archive(a->data, a->size) || a->size < 8)
        return -1;
    a->count = rd32(a->data + 4);
    if (a->size < 8 + (size_t)a->count * 8)
        return -1;
    a->entries = (dw4_afs_entry *)calloc(a->count ? a->count : 1, sizeof(*a->entries));
    if (!a->entries)
        return -1;
    for (i = 0; i < a->count; i++) {
        a->entries[i].offset = rd32(a->data + 8 + 8 * i);
        a->entries[i].size = rd32(a->data + 12 + 8 * i);
    }
    return 0;
}

int dw4_afs_open(dw4_afs *a, const char *path)
{
    memset(a, 0, sizeof(*a));
    if (read_all(path, &a->data, &a->size) != 0)
        return -1;
    a->owns_data = 1;
    if (parse_table(a) != 0) {
        dw4_afs_close(a);
        return -1;
    }
    return 0;
}

int dw4_afs_open_table(dw4_afs *a, const char *path)
{
    memset(a, 0, sizeof(*a));
    if (read_all(path, &a->data, &a->size) != 0)
        return -1;
    a->owns_data = 1;
    if (parse_table(a) != 0) {
        dw4_afs_close(a);
        return -1;
    }
    /* A table-only view keeps the mmap-less simplicity but frees the payload. */
    free(a->data);
    a->data = NULL;
    a->size = 0;
    return 0;
}

int dw4_afs_open_mmap(dw4_afs *a, const char *path)
{
#if defined(_WIN32)
    return dw4_afs_open(a, path);
#else
    struct stat st;
    int fd;
    void *p;

    memset(a, 0, sizeof(*a));
    fd = open(path, O_RDONLY);
    if (fd < 0 || fstat(fd, &st) != 0 || st.st_size < 8) {
        if (fd >= 0)
            close(fd);
        return -1;
    }
    p = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (p == MAP_FAILED)
        return -1;
    a->data = (uint8_t *)p;
    a->size = (size_t)st.st_size;
    a->mapped = 1;
    if (parse_table(a) != 0) {
        dw4_afs_close(a);
        return -1;
    }
    return 0;
#endif
}

void dw4_afs_close(dw4_afs *a)
{
    if (a->mapped) {
#if !defined(_WIN32)
        munmap(a->data, a->size);
#endif
        a->data = NULL;
    } else if (a->owns_data) {
        free(a->data);
    }
    free(a->entries);
    memset(a, 0, sizeof(*a));
}

const uint8_t *dw4_afs_entry_data(const dw4_afs *a, uint32_t index)
{
    if (index >= a->count || !a->data)
        return NULL;
    if ((size_t)a->entries[index].offset + a->entries[index].size > a->size)
        return NULL;
    return a->data + a->entries[index].offset;
}

long dw4_afs_extract(const dw4_afs *a, uint32_t index, const char *out_path)
{
    const uint8_t *p = dw4_afs_entry_data(a, index);
    FILE *f;

    if (!p)
        return -1;
    f = fopen(out_path, "wb");
    if (!f)
        return -1;
    if (fwrite(p, 1, a->entries[index].size, f) != a->entries[index].size) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return (long)a->entries[index].size;
}
