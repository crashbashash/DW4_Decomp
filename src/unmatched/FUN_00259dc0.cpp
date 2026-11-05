/* C++ translation unit (retail kept this function's exception index record): the pooled-string token passed
 * to FUN_001ca620 is owned by a StringRef, released after the call (retail table: one range, destroy at sp+92,
 * out-of-line copy StringRef_Destruct_00130720 = config/SLUS-20836/unit-objects.json duplicate __dt__9StringRefFv). */
typedef struct Rc { int w0; int refs; } Rc;
typedef struct L { int w0, w4; volatile int n; int cap; int *data; } L;
typedef struct S { char pad[36]; L *f36; void *f40; } S;
extern "C" {
Rc *FUN_002b90e0(int);
L *FUN_002caa70(int);
int FUN_002eb010(int);
int FUN_0025a550(S *, int);
int FUN_00463c70(S *);
int List_Resize(L *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(void *);
extern int DAT_00498728[4];
extern int DAT_00586f20[4];
void FUN_00259dc0(S *arg0, int arg1, int arg2);
}
/* matching construct: retail writes a zero byte to a word-sized frame temporary (sp+88, sp+84) before each
 * "release the old reference, store the new one" pair; a one-byte class temporary with a zeroing constructor
 * takes those slots (below the named StringRef at sp+92).  Its purpose is unknown (hypothesis, no finding yet). */
struct ScratchFlag { volatile char c; ScratchFlag() { c = 0; } };
class StringRef {
public:
    int p;
    StringRef(int s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int FUN_001ca620(void *, StringRef *);
void FUN_00259dc0(S *arg0, int arg1, int arg2) {
    int var_v0;
    int obj;
    Rc *t;
    int n;
    L *l;
    int *hd;
    int cnt;
    int dv;
    ScratchFlag();
    t = (Rc *)arg0->f40;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f40 = FUN_002b90e0(0);
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            obj = FUN_002eb010(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            DAT_00586f20[0] = obj;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    {
        StringRef name(var_v0);
        FUN_001ca620(arg0->f40, &name);
    }
    ScratchFlag();
    t = (Rc *)arg0->f36;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f36 = FUN_002caa70(0);
    l = arg0->f36;
    n = l->n;
    if (n < l->cap) {
        l->n = l->n + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    dv = DAT_00498728[0];
    l->data[n] = dv;
    FUN_0025a550(arg0, dv);
    if (arg2 != 0) {
        FUN_00463c70(arg0);
    }
}
