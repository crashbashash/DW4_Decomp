#include "dw4/reflected.h"

extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int strcmp(void *, int);
extern int DAT_00586f20[4];
}
extern "C" beSystem *DAT_0058a1b8[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    void *p;
    StringRef(void *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
/* The copied token is returned through a hidden return pointer. */
extern "C" StringRef StringList_CopyRetained(void *, int);

extern "C" void CFLsetName(int arg0) {
    int v2;
    void *v;
    igStringRefList *list;
    int n;
    bool found;
    int i;

    found = false;
    list = (igStringRefList *)DAT_0058a1b8[0]->_readFileList;
    n = list->_count;
    i = 0;
    if (0 < n) {
    do {
        {
            StringRef name = StringList_CopyRetained(list, i);
            if (strcmp(name.p, arg0) == 0) {
                found = true;
                break;
            }
        }
        i++;
    } while (i < n);
    }
    if (!((int)found & 0xff)) {
        if (arg0 == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                v2 = FUN_002eb010(16);
                if (v2 != 0) {
                    v2 = StringPool_Construct(v2);
                }
                DAT_00586f20[0] = v2;
            }
            v = StringPool_Intern(DAT_00586f20[0], arg0);
        }
        {
            StringRef fresh(v);
            StringList_AppendRetained(list, &fresh);
        }
    }
}
