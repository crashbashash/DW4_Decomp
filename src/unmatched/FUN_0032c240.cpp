extern "C" {
struct Text { int word0; int references; char *chars; int length; };
extern int strlen(char *);
extern char _toupper(char);
extern Text *FUN_002b9500(int);
extern int FUN_002eb010(int);
extern int FUN_0030b3c0(Text *, char *);
extern int FUN_0030b460(Text *, char *, int, int);
extern int Memory_GetAllocatorBySelector(int);
extern int StringChunk_ReleaseHeader(int, int *);
extern int StringPool_Construct(int);
extern char *StringPool_Intern(int, char *);
extern int igObject_Destroy(Text *);
extern char *DAT_004c22f0[4];
extern char DAT_004ffbe8[];
extern char DAT_004ffbf0[];
extern int DAT_00586f20[4];
extern int DAT_00587048[4];
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *text) : p(text) {}
    ~igSmartPointer() {
        T *text = p;
        if (text != 0) {
            text->references = text->references - 1;
            if ((text->references & 0x7FFFFF) == 0) {
                igObject_Destroy(text);
            }
        }
    }
    T *get() const { return p; }
};
struct StringRef {
    char *p;
    StringRef(char *chars) {
        char *interned;
        if (chars == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(16);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            interned = StringPool_Intern(DAT_00586f20[0], chars);
        }
        p = interned;
    }
    StringRef(const StringRef &other) : p(other.p) {
        if (p != 0) {
            ((int *)p)[-1] = ((int *)p)[-1] + 1;
        }
    }
    ~StringRef() {
        char *chars = p;
        if (chars != 0) {
            int *header = (int *)chars - 2;
            int left = header[1] - 1;
            header[1] = left;
            if (left == 0) {
                StringChunk_ReleaseHeader(header[0], header);
            }
        }
    }
};
static inline void append(const igSmartPointer<Text> &ref, char *chars) {
    Text *text = ref.p;
    int length = text->length;
    FUN_0030b460(text, chars, length, strlen(chars));
}
extern "C" StringRef FUN_0032c240(char *prefix, char *path) {
    char *chars;
    int limit, i;
    char c;
    igSmartPointer<Text> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    if (prefix == 0) {
        FUN_0030b3c0(text.get(), path);
    } else if (*prefix == 0x63) {
        FUN_0030b3c0(text.get(), prefix);
        c = *path;
        if (c != 0x5C && c != 0x2F) {
            append(text, DAT_004ffbe8);
        }
        append(text, path);
        append(text, DAT_004ffbf0);
        limit = strlen(path) + 8;
        for (i = 7; i < limit; i++) {
            chars = text.get()->chars + i;
            if (*chars == 0x2F) {
                *chars = 0x5C;
            } else {
                *chars = _toupper(*chars);
            }
        }
    } else {
        FUN_0030b3c0(text.get(), prefix);
        append(text, path);
    }
    chars = text.get()->chars;
    if (chars == 0) {
        chars = DAT_004c22f0[0];
    }
    StringRef result(chars);
    return result;
}
