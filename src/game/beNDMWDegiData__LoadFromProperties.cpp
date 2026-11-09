/* Property-record loader. Copies the scalar, string, id-list and index-list records of the property
 * set arg1 into the data block of the beNDMWDegiData arg0 (its _data field, +28), then calls
 * beNDMWDegiData__UpdateFieldsFromData(arg0). PropDest is a private view of that block.
 * Matching constructs: KeyHolder is a const int so the search key is spilled to a stack slot; the
 * SEARCH/FIND* macros are one search loop spelled with explicit induction locals because their
 * register order (key < constant -1; count < offset < pointer < data pointer) is decided by
 * declaration order. */
#include "dw4/reflected.h"
class IdObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); 
    virtual int GetId();
};
struct StrObj { int p0; int references; int p8; unsigned short *chars; };
struct RecByte { int p[3]; unsigned char v; };
struct RecInt { int p[3]; int v; };
struct RecObjList { int p[3]; igObjectList *v; };
struct RecByteList { int p[3]; igUnsignedCharList *v; };
struct RecIntList { int p[3]; igIntList *v; };
struct RecStrList { int p[3]; igStringObjList *v; };
struct PropDest {
    unsigned char b0; char p1[3]; int f4; int f8[8]; unsigned short s40[9]; char p58[14];
    int f72, f76, f80, f84, f88, f92, f96;
    int ids100[36]; int ids244[12]; unsigned char b292[52]; int ids344[96];
    int f728; int idx732[3]; int idx744[5]; int f764; int idx768[5]; int f788;
    unsigned char b792[1024]; unsigned char b1816[12]; int w1828[16]; unsigned char b1892[16];
    int w1908[16]; int w1972[16]; int w2036[16]; char pad2100[512]; int w2612[16];
};
extern "C" {
RecByte *igProperty_GetRecordByte(int, void *);
RecInt *igProperty_GetRecord(int, void *);
RecObjList *igProperty_GetRecordFolder(int, void *);
RecByteList *igProperty_GetRecordArray(int, void *);
RecStrList *FUN_003a92e0(int, void *);
RecIntList *FUN_003a9250(int, void *);
void strcpy(void *, void *);
void ObjectList_ResizeRetained(void *, int);
void igObject_Destroy(void *);
void beNDMWDegiData__UpdateFieldsFromData(void *);
extern int DAT_00517e58[4];
extern int DAT_00517e60[4];
extern int DAT_00517e68[4];
extern int DAT_00517e70[4];
extern int DAT_00517e78[4];
extern int DAT_00517e80[4];
extern int DAT_00517e88[4];
extern int DAT_00517e90[4];
extern int DAT_00517ea0[4];
extern int DAT_00517eb0[4];
extern int DAT_00517eb8[4];
extern int DAT_00517ec0[4];
extern int DAT_00517ed0[4];
extern int DAT_00517ee0[4];
extern int DAT_00517ef0[4];
extern int DAT_00517f00[4];
extern int DAT_00517f08[4];
extern int DAT_00517f18[4];
extern int DAT_00517f28[4];
extern int DAT_00517f38[4];
extern int DAT_00517f48[4];
extern int DAT_00517f50[4];
extern int DAT_00517f60[4];
extern int DAT_00517f70[4];
extern int DAT_00517f80[4];
extern int DAT_00517f90[4];
extern int DAT_00517fa0[4];
extern int DAT_00517fb0[4];
extern int DAT_00517fc0[4];
/* matching construct: const keeps the search key memory-resident (retail spills it); no destructor, so no cleanup record */
struct KeyHolder { int v; };
struct RP {
    StrObj *p;
    RP(StrObj *x) { p = x; }
    ~RP() { StrObj *r = p; if (r != 0) { r->references = r->references - 1; if ((r->references & 0x7fffff) == 0) igObject_Destroy(r); } }
};
#define IDS(DST, REC, CAP, RESIZE) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; int i; if (RESIZE) { if (l->_count > CAP) ObjectList_ResizeRetained(l, CAP); } i = 0; if (0 < l->_count) { do { DST[i] = ((IdObject **)l->_data)[i]->GetId(); i++; } while (i < l->_count); } if (i < CAP) { do { DST[i] = -1; i++; } while (i < CAP); } }
#define BYTES(DST, FN, REC) { igUnsignedCharList *l = FN(arg1, REC)->v; int i = 0; if (0 < l->_count) { do { DST[i] = (*(unsigned char **)&l->_data)[i]; i++; } while (i < l->_count); } }
#define SEARCH(OUT, LBL) { if (0 < n) { q = (int *)t->_data; kv = (*(int const *)&kk.v); do { if (kv == *q) { r = j; goto LBL; } j++; q++; } while (j < n); } r = -1; LBL: OUT = r; }
#define FINDN(DST, REC, N, OFF, LBL) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igIntList *t = (igIntList *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; int a; int j; int r; int n; int o; char *pp; int *q; int kv; KeyHolder kk; a = 0; o = 0; pp = (char *)d; do { int v = *(int *)(l->_data + o); if (v == 0) *(int *)(pp + OFF) = -1; else { kk.v = v; j = 0; n = t->_count; SEARCH(*(int *)(pp + OFF), LBL) } a++; o += 4; pp += 4; } while (a < N); }
#define FIND1(DSTV, REC, LBL) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igIntList *t = (igIntList *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; int j; int r; int n; int *q; int kv; KeyHolder kk; int v = (int)((IdObject **)l->_data)[0]; if (v == 0) DSTV = -1; else { kk.v = v; j = 0; n = t->_count; SEARCH(DSTV, LBL) } }
#define FINDV(DST, REC, OFF, LBL) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igIntList *t = (igIntList *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; int a; int j; int r; int n; int o; char *pp; int *q; int kv; KeyHolder kk; if (0 < l->_count) { a = 0; o = 0; pp = (char *)d; do { int v = *(int *)(l->_data + o); if (v == 0) *(int *)(pp + OFF) = -1; else { kk.v = v; j = 0; n = t->_count; SEARCH(*(int *)(pp + OFF), LBL) } a++; o += 4; pp += 4; } while (a < l->_count); } }
#define INTS(DST, FN, REC) { igIntList *l = FN(arg1, REC)->v; int i = 0; if (0 < l->_count) { do { DST[i] = ((int *)l->_data)[i]; i++; } while (i < l->_count); } }
void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *arg0, int arg1) {
    PropDest *d = (PropDest *)arg0->_data;
    d->b0 = igProperty_GetRecordByte(arg1, &DAT_00517e58[0])->v;
    d->f4 = igProperty_GetRecord(arg1, &DAT_00517e60[0])->v;
    d->f72 = igProperty_GetRecord(arg1, &DAT_00517e68[0])->v;
    d->f76 = igProperty_GetRecord(arg1, &DAT_00517e70[0])->v;
    d->f80 = igProperty_GetRecord(arg1, &DAT_00517e78[0])->v;
    d->f84 = igProperty_GetRecord(arg1, &DAT_00517e80[0])->v;
    d->f88 = igProperty_GetRecord(arg1, &DAT_00517e88[0])->v;
    {
        igStringObjList *sl = (igStringObjList *)igProperty_GetRecordFolder(arg1, &DAT_00517e90[0])->v;
        if (sl->_count != 0) {
            RP s(((StrObj **)sl->_data)[0]);
            if (s.p != 0) s.p->references = s.p->references + 1;
            {
                unsigned short *src;
                unsigned short *base;
                int i;
                unsigned short *dst;
                base = &d->s40[0];
                i = 0;
                dst = base;
                src = s.p->chars;
            L1: dst[1] = *src;
                if (*src == 0) { dst = base + i; goto T; }
                src++; dst++; i++; goto L1;
            B:  dst[1] = 0; dst++; i++;
            T:  if (i < 8) goto B;
                base[0] = 0xffff;
            }
        }
    }
    {
        RecStrList *rs = FUN_003a92e0(arg1, &DAT_00517ea0[0]);
        void *str = (void *)rs->v;
        if (str != 0) strcpy(&d->f8[0], str);
    }
    d->f92 = igProperty_GetRecord(arg1, &DAT_00517eb0[0])->v;
    d->f96 = igProperty_GetRecord(arg1, &DAT_00517eb8[0])->v;
    IDS(d->ids100, &DAT_00517ec0[0], 36, 1)
    IDS(d->ids244, &DAT_00517ed0[0], 12, 1)
    BYTES(d->b292, igProperty_GetRecordArray, &DAT_00517ee0[0])
    IDS(d->ids344, &DAT_00517ef0[0], 96, 0)
    d->f728 = igProperty_GetRecord(arg1, &DAT_00517f00[0])->v;
    FINDN(d->idx732, &DAT_00517f08[0], 3, 732, f1)
    FINDN(d->idx744, &DAT_00517f18[0], 5, 744, f2)
    FIND1(d->f764, &DAT_00517f28[0], f3)
    FINDV(d->idx768, &DAT_00517f38[0], 768, f4)
    FIND1(d->f788, &DAT_00517f48[0], f5)
    BYTES(d->b792, igProperty_GetRecordArray, &DAT_00517f50[0])
    BYTES(d->b1816, igProperty_GetRecordArray, &DAT_00517f60[0])
    INTS(d->w1828, FUN_003a9250, &DAT_00517f70[0])
    BYTES(d->b1892, igProperty_GetRecordArray, &DAT_00517f80[0])
    INTS(d->w1908, FUN_003a9250, &DAT_00517f90[0])
    INTS(d->w1972, FUN_003a9250, &DAT_00517fa0[0])
    INTS(d->w2036, FUN_003a9250, &DAT_00517fb0[0])
    INTS(d->w2612, FUN_003a9250, &DAT_00517fc0[0])
    beNDMWDegiData__UpdateFieldsFromData(arg0);
}
}
