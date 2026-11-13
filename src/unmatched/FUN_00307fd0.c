int sscanf();
void *FUN_002b9500();
void *FUN_002baff0();
int FUN_00305d30();
int FUN_003061c0();
int igStringObj_Set();
int FUN_0030b980();
int igObject_Destroy();
int igObject_GetAllocator();
extern char *DAT_004c22f0;
extern char DAT_004f7910[];
extern char DAT_004fb280[];
extern int DAT_005871c0;
typedef struct IniIncludeText { char pad[4]; int _refCount; char *text; int length; } IniIncludeText;
typedef struct IniIncludeObject { char pad[4]; int _refCount; } IniIncludeObject;
typedef struct IniIncludeFile { char pad[12]; char *dir; } IniIncludeFile;
static inline char *text(IniIncludeText *s) {
    char *t = s->text;
    if (t == 0) {
        return DAT_004c22f0;
    }
    return t;
}
void FUN_00307fd0(void *self, IniIncludeFile *file, char *line, int lineNo, int overwrite) {
    char open;
    char close;
    IniIncludeObject *include;
    IniIncludeText *dir;
    char path[4096];
    int found;
    IniIncludeObject *held;
    IniIncludeText *heldDir;

    if (sscanf(line, DAT_004fb280, &open, path, &close) != 3) {
        return;
    }
if (open != '"' && open != '<') return; if ((open == '"' && close != '"') || (open == '<' && close != '>')) return;     if (DAT_005871c0 < 12) {
        DAT_005871c0 += 1;
        *(IniIncludeObject **)&include = FUN_002baff0(igObject_GetAllocator(self));
        found = 0;
        *(IniIncludeText **)&dir = FUN_002b9500(igObject_GetAllocator(self));
        igStringObj_Set(dir, file->dir);
        FUN_0030b980(dir);
        if (dir->length != 0) {
            held = include; found = FUN_00305d30(held, path, text(dir)) & 0xFF;
        }
        if (found != 0 || FUN_00305d30(include, path, DAT_004f7910) != 0) {
            FUN_003061c0(self, include, overwrite);
        }
        DAT_005871c0 -= 1;
        heldDir = dir;
        if (heldDir != 0) {
            heldDir->_refCount = heldDir->_refCount - 1;
            if (((unsigned long long)((long long)heldDir->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(heldDir);
            }
        }
        held = include;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }

}
