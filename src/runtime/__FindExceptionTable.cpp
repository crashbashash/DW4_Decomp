typedef struct ExceptionTableIndex {
    char *function_address;
    unsigned int function_size;
    char *exception_table;
} ExceptionTableIndex;

typedef struct ExceptionInfo {
    char *current_function;
    char *exception_record;
    char *action_pointer;
    ExceptionTableIndex *exception_table_start;
    ExceptionTableIndex *exception_table_end;
} ExceptionInfo;

extern "C" int FUN_00102620(ExceptionInfo *info, char *return_address);
extern "C" char *FUN_001025d0(char *exception_record);
extern "C" char *__DecodeUnsignedNumber(char *p, unsigned int *out);

static inline ExceptionTableIndex *findIndexEntry(ExceptionTableIndex *table, unsigned int count, char *return_address) {
    int lo, mid, hi;
    ExceptionTableIndex *entry;
    for (lo = 0, hi = count - 1; lo <= hi;) {
        entry = &table[mid = (lo + hi) >> 1];
        if (return_address < entry->function_address) {
            hi = mid - 1;
        } else if (return_address > entry->function_address + (entry->function_size & ~1)) {
            lo = mid + 1;
        } else {
            return entry;
        }
    }
    return 0;
}

extern "C" void __FindExceptionTable(char *return_address, ExceptionInfo *info) {
    ExceptionTableIndex *entry;
    char *ranges;
    unsigned int offset;
    unsigned int pc;
    unsigned int delta;
    unsigned int length;
    unsigned int actions;

    info->exception_record = 0;
    info->action_pointer = 0;
    if (!FUN_00102620(info, return_address)) {
        return;
    }
    return_address = (char *)((int)return_address & ~1L);
    entry = findIndexEntry(info->exception_table_start, info->exception_table_end - info->exception_table_start, return_address);
    if (!entry) {
        return;
    }
    if (entry->function_size & 1) {
        info->exception_record = (char *)&entry->exception_table;
    } else {
        info->exception_record = entry->exception_table;
    }
    info->current_function = entry->function_address;
    offset = return_address - entry->function_address;
    ranges = FUN_001025d0(info->exception_record);
    for (pc = 0;;) {
        ranges = __DecodeUnsignedNumber(ranges, &delta);
        if (delta == 0) {
            return;
        }
        ranges = __DecodeUnsignedNumber(ranges, &length);
        ranges = __DecodeUnsignedNumber(ranges, &actions);
        pc += delta;
        if (offset < pc) {
            return;
        }
        pc += length;
        if (offset <= pc) {
            break;
        }
    }
    info->action_pointer = info->exception_record + actions;
}
