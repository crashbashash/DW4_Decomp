/* IgMemoryPoolContextInfo slot 180: write the 46 original context names (Bootstrap, Default,
 * Current, NonTracked, ...) into the name field of each 144-byte context record. Each name is
 * copied with a 127-character limit and the 128th byte is cleared explicitly. Called by the
 * constructor and the destructor. strncpy is a strncpy-like bounded string copy (dest, source,
 * limit). */
#include "dw4/reflected.h"

#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_NAME_LIMIT 0x7F      /* 127-char copy, then an explicit terminator */

/* One record: 4-byte first word, 128-byte inline name, 12 further bytes. */
typedef struct ContextRecord {
    int firstWord;
    char name[128];
    char rest[12];
} ContextRecord;

/* The 46 records follow the 20-byte object header.  Retail steps one pointer
 * by whole records from the context base, so that pointer sits 20 bytes before
 * the record it works on; this view reproduces it (name is 24 bytes in). */
typedef struct ContextPrefixedRecord {
    char header[20];
    ContextRecord record;
} ContextPrefixedRecord;

int strncpy();
extern int g_memoryContextNames[4];

void igMemoryPoolContextInfo_InitializeRecordNames(igMemoryPoolContextInfo *self) {
    int index;
    ContextPrefixedRecord *entry;

    index = 0;
    do {
        entry = (ContextPrefixedRecord *)((char *)self + index * sizeof(ContextRecord));
        strncpy(entry->record.name, g_memoryContextNames[index], CONTEXT_NAME_LIMIT);
        index += 1;
        entry->record.name[CONTEXT_NAME_LIMIT] = 0;
    } while (index < CONTEXT_RECORD_COUNT);
}
