struct MediaPathBuffer { int vt; int refCount; char *text; int length; };
struct MediaHandleRow { char *name; int p4; int p8; };
struct MediaHandleTable { char pad[12]; MediaHandleRow *rows; };
struct MediaPathFields { char pad[28]; MediaHandleTable *handles; MediaPathBuffer *conversion; };
extern "C" {
extern bool GPR_00554de0;
extern char *DAT_004c2650[];
extern char *DAT_00587368;
extern char DAT_004ffbe8[];
extern char DAT_004ffbf0[];
extern char *DAT_004c22f0;
extern int DAT_00586f20;
char *strchr(char *, int);
int strlen(const char *);
int FUN_0012a918(const char *, const char *, int);
void FUN_0030b3c0(MediaPathBuffer *, char *);
void FUN_0030b460(MediaPathBuffer *, const char *, int, int);
void FUN_0030b420(MediaPathBuffer *);
int FUN_0012c4c8(int);
int FUN_002eb010(int);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
void StringChunk_ReleaseHeader(int, int *);
void FUN_0032e130(MediaPathFields *self, int index, char **path);
}
static inline void appendPath(const char *text, MediaPathBuffer *buffer) {
    int length = buffer->length;
    FUN_0030b460(buffer, text, length, strlen(text));
}
void FUN_0032e130(MediaPathFields *self, int index, char **path) {
    bool usePrefix = true;
    bool isDisc = GPR_00554de0;
    char *colon = strchr(*path, ':');
    char *text;
    int prefix;
    int end;
    int i;
    char *interned;
    int stop;
    char *p;
    MediaHandleRow *row;
    int j;
    int v;
    if (colon != 0) {
        prefix = colon - *path;
        for (i = 0; i < 5; i++) {
            char **device = &DAT_004c2650[i];
            if (prefix == strlen(*device) && FUN_0012a918(*path, *device, prefix) == 0) {
                if (i < 2) {
                    isDisc = true;
                } else {
                    isDisc = false;
                }
                usePrefix = false;
                break;
            }
        }
    }
    if (usePrefix) {
        if (isDisc) {
            FUN_0030b3c0(self->conversion, DAT_00587368);
            if (**path != '\\' && **path != '/') {
                appendPath(DAT_004ffbe8, self->conversion);
            }
            appendPath(*path, self->conversion);
            end = strlen(*path) + 6;
            for (i = 6; i < end; i++) {
                p = self->conversion->text + i;
                if (*p == '/') {
                    *p = '\\';
                } else {
                    *p = FUN_0012c4c8(*p);
                }
            }
            appendPath(DAT_004ffbf0, self->conversion);
        } else {
            FUN_0030b3c0(self->conversion, DAT_00587368);
            appendPath(*path, self->conversion);
        }
        text = self->conversion->text;
        text = (text == 0) ? DAT_004c22f0 : text;
    } else if (isDisc && strchr(*path, ';') == 0) {
        FUN_0030b3c0(self->conversion, *path);
        stop = strlen(*path);
        for (j = 6; j < stop; j++) {
            p = self->conversion->text + j;
            if (*p == '/') {
                *p = '\\';
            } else {
                *p = FUN_0012c4c8(*p);
            }
        }
        appendPath(DAT_004ffbf0, self->conversion);
        text = self->conversion->text;
        text = (text == 0) ? DAT_004c22f0 : text;
    } else {
        text = *path;
    }
    {
        row = &self->handles->rows[index];
        if (DAT_00586f20 == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20 = v;
        }
        interned = StringPool_Intern(DAT_00586f20, text);
        if (row->name != 0) {
            int *hdr = (int *)row->name - 2;
            int r = ((int *)row->name)[-1] - 1;
            ((int *)row->name)[-1] = r;
            if (r == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
        row->name = interned;
    }
    FUN_0030b420(self->conversion);
}
