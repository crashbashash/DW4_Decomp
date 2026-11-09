extern "C" {
struct TextBuffer { int vtable; unsigned int refCount; char *text; };
struct PathEntry { int vtable; unsigned int refCount; char *name; int f12; short left; short right; };
struct PathEntryList { int vtable; unsigned int refCount; int count; int capacity; PathEntry **data; };
unsigned int strlen(const char *);
void *memset(void *, int, unsigned int);
char *strncpy(char *, const char *, unsigned int);
int strcmp(const char *, const char *);
void FUN_0030b3c0(TextBuffer *buffer, const char *text);
void FUN_0030b5c0(TextBuffer *buffer);
void FUN_0030b5f0(TextBuffer *buffer, int *value);
void FUN_00333630(PathEntry *entry, char *path);
void igNamedObject_SetName(PathEntry *object, const char *name);
extern char *DAT_004c22f0[4];
extern TextBuffer *DAT_005875e0[4];
extern PathEntryList *DAT_00587620[4];
/* matching construct: a small sweep of spellings */
int FUN_00333440(const char *name);
}

int FUN_00333440(const char *name) {
    int left;
    int right;
    char digits[16];
    char path[256];
    int close;
    unsigned int i;
    int k;
    int n;
    if (DAT_00587620[0]) {
        close = -1;
        if (name[0] == '[') {
            for (i = 1; i < strlen(name); i++) {
                if (name[i] == ']') {
                    close = i + 1;
                    break;
                }
            }
            if (close != -1 && close >= 3) {
                PathEntry *entry;
                memset(digits, 0, 16);
                strncpy(digits, name + 1, 1);
                FUN_0030b3c0(DAT_005875e0[0], digits);
                FUN_0030b5f0(DAT_005875e0[0], &left);
                strncpy(digits, name + 3, close - 4);
                FUN_0030b3c0(DAT_005875e0[0], digits);
                FUN_0030b5f0(DAT_005875e0[0], &right);
                entry = DAT_00587620[0]->data[0];
                igNamedObject_SetName(entry, name);
                entry->left = left;
                entry->right = right;
                return 0;
            }
        }
        n = DAT_00587620[0]->count;
        FUN_0030b3c0(DAT_005875e0[0], name);
        FUN_0030b5c0(DAT_005875e0[0]);
        for (k = 1; k < n; k++) {
            FUN_00333630(DAT_00587620[0]->data[k], path);
            const char *text = DAT_005875e0[0]->text;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            if (strcmp(text, path) == 0) {
                return k;
            }
        }
    }
    return -1;
}
