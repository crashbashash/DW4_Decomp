/* Renames record `recordIndex` of the context: copies at most 127 characters into the record's
 * inline 128-byte name field, terminates it, and renames the record's bound named object (if any)
 * to match. Out-of-range indices are ignored. The context holds 46 records of 144 bytes starting
 * at +0x14, each with a 128-byte inline name at +4 (docs/engine/context-lifecycle.md, finding
 * #896; the record view matches src/engine/context-record-name.cpp). */
int strncpy();
int igNamedObject_SetName();

#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_RECORD_SIZE 0x90
#define CONTEXT_RECORDS_OFFSET 0x14
#define CONTEXT_RECORD_NAME_MAX 0x7F

void Gap__Core__igMemoryPoolContextInfo__vfunc_56(int self, int recordIndex, int name) {
    int boundObject;
    void *record;

    if ((recordIndex >= 0) && (recordIndex < CONTEXT_RECORD_COUNT)) {
        record = (void *)(self + (recordIndex * CONTEXT_RECORD_SIZE) + CONTEXT_RECORDS_OFFSET);
        strncpy((char *)record + 4, name, CONTEXT_RECORD_NAME_MAX);
        *(char *)((char *)(record) + 131) = 0;
        boundObject = *(int *)((char *)(record) + 132);
        if (boundObject != 0) {
            igNamedObject_SetName(boundObject, name);
        }
    }
}
