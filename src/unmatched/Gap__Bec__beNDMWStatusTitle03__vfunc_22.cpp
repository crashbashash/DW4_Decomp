/* 0x00441040 - Gap__Bec__beNDMWStatusTitle03__vfunc_22. Two interned strings appended to message lists (pool created on first use, refcount released inline) then the message script; the constant string address is still tested (if-else layout with the null arm first); price switch with an uninitialised default; alternate compiler -O3,p, C++ without exceptions. */
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int beNDMWWindow_PresentModelAtOrigin(void *, int *, int, int *, int *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_0051ac08[4];
extern int DAT_0051ac10[4];
extern int DAT_0051af90[4];
extern int DAT_0051acb0[4];
extern int DAT_0051ad60[4];
extern void *DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
struct Sh { char p[44]; unsigned f44; char q[12]; int f60; int f64; };
/* intern `text` (the pool singleton is created on first use) and append the token to `field` */
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }
extern int DAT_0051afa0[4];
extern int DAT_0051ace0[4];
extern int DAT_0051afb0[4];
extern "C" void Gap__Bec__beNDMWStatusTitle03__vfunc_22(Sh *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051af90, 0, DAT_0051ac08, DAT_0051ac10);
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051acb0)
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051ace0)
    INTERN_APPEND(arg0->f60, DAT_0051afa0)
    INTERN_APPEND(arg0->f64, DAT_0051afb0)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051ad60, 0);
}
