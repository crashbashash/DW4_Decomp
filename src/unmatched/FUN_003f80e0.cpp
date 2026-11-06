/* Index of the evolution-database record whose name string is the interned copy of arg1 (0..15),
 * or 0; the database object is fetched from the messenger on first use. The interned name lives in
 * a StringRef for the whole search (released at both exits); the record compare is a pointer
 * compare of the pooled tokens. alternate compiler -O3,p */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int);
char *beDataBase_GetRecordString(int, int, int *);
int *beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int igObject_Destroy(void *);
extern int DAT_00518bc8[4];
extern int DAT_00519420[4];
extern int DAT_00519430[4];
extern int DAT_00519438[4];
extern int DAT_00586f20[4];
int FUN_003f80e0(beNDMWGameRam *arg0, int arg1);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
struct R { int w0; int rc; };
int FUN_003f80e0(beNDMWGameRam *arg0, int arg1) {
    int s2;
    char *s1;
    int var_v0_2;
    struct R *t;
    struct R *a0;
    char *var_v0;
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    StringRef name(var_v0);
    s2 = 0;
    for (;;) {
        s1 = name.p;
        if (arg0->_dBShinka == 0) {
            beMessenger_SendNamed(arg0->_messenger, DAT_00519438, DAT_00519430, 0, DAT_00519420);
            t = (struct R *)beMessenger_GetObject(arg0->_messenger, 0);
            if (t != 0) {
                t->rc = t->rc + 1;
            }
            a0 = (struct R *)arg0->_dBShinka;
            if (a0 != 0) {
                a0->rc = a0->rc - 1;
                if ((a0->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->_dBShinka = (int)t;
        }
        if (beDataBase_GetRecordString(arg0->_dBShinka, s2, DAT_00518bc8) == s1) {
            return s2;
        }
        s2 += 1;
        if (s2 >= 0x10) {
            return 0;
        }
    }
}
