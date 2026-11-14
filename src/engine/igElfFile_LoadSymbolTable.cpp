struct ElfResult { int w; ElfResult() {} ElfResult(const ElfResult &o) : w(o.w) {} bool operator==(const ElfResult &o) const { return w == o.w; } };
struct ElfSymbolEntry { int name; unsigned value; int size; unsigned char info; };
class ElfSymbolSink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void Add(const char *name, void *value, unsigned size, int flags); };
class ElfSymbolFileView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual ElfResult Close(); virtual ElfResult Load(int offset, int size, void *dest); virtual ElfResult LoadSymbols(); virtual void d26(); virtual ElfResult ReadString(int offset, char *text, int limit, int flags);
    char pad0[4]; int path; char pad12[76]; char *strings; int symbolCount; };
extern "C" {
extern ElfResult DAT_004fb410;
extern ElfResult DAT_004fb418;
extern char DAT_004fde50[];
void igReport_Printf(char *, int);
void igReport_Flush(void);
ElfSymbolEntry *igElfFile_GetSymbol(ElfSymbolFileView *, int);
void igSymbolTable_SetCapacity(ElfSymbolSink *, int);
void igSymbolTable_SetHashCapacity(ElfSymbolSink *, int);
void igSymbolTable_SetAddressRange(ElfSymbolSink *, unsigned, unsigned);
void igSymbolTable_ReserveStorage(ElfSymbolSink *);
ElfResult igElfFile_LoadSymbolTable(ElfSymbolFileView *self, ElfSymbolSink *sink, int functionsOnly);
}
static inline void prepareSink(ElfSymbolSink *sink, int count, unsigned low, unsigned top) {
    igSymbolTable_SetCapacity(sink, count);
    igSymbolTable_SetHashCapacity(sink, count * 4);
    igSymbolTable_SetAddressRange(sink, low & ~1023, top);
    igSymbolTable_ReserveStorage(sink);
}
ElfResult igElfFile_LoadSymbolTable(ElfSymbolFileView *self, ElfSymbolSink *sink, int functionsOnly) {
    char text[264];
    unsigned low;
    int j;
    int i;
    ElfSymbolEntry *entry;
    int count;
    unsigned high;
    low = -1U;
    high = 0;
    count = 0;
    if (self->symbolCount == 0) {
        if (self->LoadSymbols() == DAT_004fb418) {
            return DAT_004fb418;
        }
    }
    if (self->symbolCount == 0) {
        igReport_Printf(DAT_004fde50, self->path);
        igReport_Flush();
        return DAT_004fb418;
    }
    if (functionsOnly == 0) {
        count = self->symbolCount;
    }
    for (i = 0; i < self->symbolCount; i++) {
        ElfSymbolEntry *sym = igElfFile_GetSymbol(self, i);
        unsigned value = sym->value;
        if (value == 0 || value == -1U) {
            continue;
        }
        if (functionsOnly != 0) {
            int info = sym->info;
            int bind = info >> 4;
            if (!(!((unsigned)(bind - 1) > 1) || bind == 0)) {
                continue;
            }
            if ((info & 15) != 2) {
                continue;
            }
            count++;
        }
        if (value < low) {
            low = value;
        }
        if (high < value) {
            high = value;
        }
    }
    high = (high & ~1023) + 1024;
    prepareSink(sink, count, low, high);
    for (j = 0; j < self->symbolCount; j++) {
        entry = igElfFile_GetSymbol(self, j);
        if (functionsOnly != 0) {
            int info = entry->info;
            int bind = info >> 4;
            if (bind == 1) {
            } else if (bind == 2) {
            } else if (bind != 0) {
                continue;
            }
            if ((info & 15) != 2) {
                continue;
            }
        }
        self->ReadString((int)(self->strings + entry->name), text, 255, 0);
        sink->Add(text, (void *)entry->value, entry->size, 0);
    }
    return DAT_004fb410;
}
