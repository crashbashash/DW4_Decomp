struct ElfResult { int w; ElfResult() {} ElfResult(const ElfResult &o) : w(o.w) {} bool operator==(const ElfResult &o) const { return w == o.w; } };
struct ElfSection { int name; int type; int flags; int addr; int offset; int size; };
class ElfFileView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual ElfResult Close(); virtual ElfResult Load(int offset, int size, void *dest);
    char pad0[4]; int path; char pad12[9]; unsigned char endian; char pad22[46]; int stringOffset; char pad72[12]; int stringsSize; void *strings; int symbolCount; void *symbols; };
extern "C" {
extern ElfResult DAT_004fb410;
extern ElfResult DAT_004fb418;
extern char DAT_004fde00[];
extern char DAT_004fde20[];
extern signed char GPR_005549b4;
int FUN_00320ee0(ElfFileView *, int, int);
ElfSection *FUN_00320ea0(ElfFileView *, int);
void FUN_00304430(char *, int);
void FUN_00304680(void);
void FUN_00320aa0(void *, int);
ElfResult Gap__Core__igElfFile__vfunc_27(ElfFileView *self);
}
ElfResult Gap__Core__igElfFile__vfunc_27(ElfFileView *self) {
    int index = FUN_00320ee0(self, 2, 0);
    ElfSection *symbols;
    ElfSection *before;
    ElfSection *after;
    ElfSection *next;
    int expected;
    if (index == -1) {
        FUN_00304430(DAT_004fde00, self->path);
        FUN_00304680();
        self->Close();
        return DAT_004fb418;
    }
    symbols = FUN_00320ea0(self, index);
    before = FUN_00320ea0(self, index - 1);
    after = FUN_00320ea0(self, index + 1);
    next = FUN_00320ea0(self, index + 2);
    if (after != 0 && after->type == 3 && after->size != self->stringOffset) {
        self->stringsSize = after->size;
        if (self->Load(after->offset, after->size, &self->strings) == DAT_004fb418) {
            return DAT_004fb418;
        }
    } else if (before != 0 && before->type == 3 && before->size != self->stringOffset) {
        self->stringsSize = before->size;
        if (self->Load(before->offset, before->size, &self->strings) == DAT_004fb418) {
            return DAT_004fb418;
        }
    } else if (next != 0 && next->type == 3 && next->size != self->stringOffset) {
        self->stringsSize = next->size;
        if (self->Load(next->offset, next->size, &self->strings) == DAT_004fb418) {
            return DAT_004fb418;
        }
    } else {
        FUN_00304430(DAT_004fde20, self->path);
        FUN_00304680();
        self->Close();
        return DAT_004fb418;
    }
    self->symbolCount = (unsigned)symbols->size >> 4;
    if (self->Load(symbols->offset, symbols->size, &self->symbols) == DAT_004fb418) {
        return DAT_004fb418;
    }
    expected = (GPR_005549b4 == 18) ? 2 : 1;
    if (self->endian != expected) {
        FUN_00320aa0(self->symbols, self->symbolCount);
    }
    return DAT_004fb410;
}
