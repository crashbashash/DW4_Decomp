/* 0x002779d8 — FUN_002779d8 (296 bytes). Starts reading the current queue entry of an lsc object (slot +32 of the 32-byte ring at +56) when entries are queued (+36): resets the transfer (+40), verifies the file name's byte-sum against the entry's key (reporting a mismatch through FUN_002777f8), then opens the file range (FUN_00269ff0), sets its limits and buffer, rewinds and starts it, and marks the entry (status 1) and the object (+2) as reading. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct LscEntry_2779d8 {
    int id;             /* 0x00 */
    char *name;         /* 0x04 */
    int key;            /* 0x08: byte-sum of name */
    int start;          /* 0x0c */
    int f16;          /* 0x10 */
    int size;           /* 0x14 */
    int status;         /* 0x18 */
    int done_bytes;     /* 0x1c */
} LscEntry_2779d8;      /* 0x20 bytes */

typedef struct Lsc_2779d8 {
    signed char pad0;
    signed char pad1;
    signed char reading;            /* 0x02 */
    char pad3[17];
    int buffer;                     /* 0x14 */
    int buffer_size;                /* 0x18 */
    int pad28;
    int head;                       /* 0x20 */
    int count;                      /* 0x24 */
    void *transfer;                 /* 0x28 */
    int size;                       /* 0x2c */
    char pad48[8];
    LscEntry_2779d8 entries[16];    /* 0x38 */
} Lsc_2779d8;

extern char E0013_s_is_different_from_entry_file_name_LSC_ExecServer[]; /* "E0013: '%s' is different from entry file name.(LSC_ExecServer)\n" */
void FUN_002777f8(const char *format, ...);
unsigned int strlen(const char *s);
void FUN_0026a238(void *transfer);
void FUN_0026a0a0(void *transfer);
void FUN_00269ff0(void *transfer, char *name, int start, int f16, int size);
void FUN_0026a300(void *transfer, int size);
void FUN_0026a9d8(void *transfer, int buffer, int buffer_size);
void FUN_0026a140(void *transfer, int position);
int FUN_0026a1b0(void *transfer);

void FUN_002779d8(Lsc_2779d8 *lsc) {
    LscEntry_2779d8 *entry = &lsc->entries[lsc->head];
    char *name;
    unsigned int length;
    unsigned int i;
    int sum;

    if (lsc->count <= 0) {
        return;
    }
    FUN_0026a238(lsc->transfer);
    FUN_0026a0a0(lsc->transfer);
    name = entry->name;
    length = strlen(name);
    sum = 0;
    for (i = 0; i < length; i++) {
        sum += (unsigned char)name[i];
    }
    if (sum != entry->key) {
        FUN_002777f8(E0013_s_is_different_from_entry_file_name_LSC_ExecServer, entry->name);
        return;
    }
    FUN_00269ff0(lsc->transfer, entry->name, entry->start, entry->f16, entry->size);
    FUN_0026a300(lsc->transfer, entry->size);
    lsc->size = entry->size;
    entry->done_bytes = 0;
    lsc->reading = 0;
    FUN_0026a9d8(lsc->transfer, lsc->buffer, lsc->buffer_size);
    FUN_0026a140(lsc->transfer, 0);
    FUN_0026a1b0(lsc->transfer);
    lsc->reading = 1;
    entry->status = 1;
}

