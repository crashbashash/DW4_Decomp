#include "dw4/igSmartPointer.h"
extern "C" {
int FUN_00150060(...);
int FUN_00150390(...);
int FUN_0015ad50(...);
int FUN_002b9500(...);
int FUN_002eb010(...);
int FUN_0030b3c0(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int igObject_GetAllocator(...);
int strcmp(...);
extern int DAT_004df5b8[4];
extern int DAT_004df5c0[4];
extern int DAT_004df5c8[4];
extern int DAT_004df5d0[4];
extern int DAT_00586f20[4];
}
class G {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,int);

};
class O0 : public igObject {
public:
 };
class O1 : public igVirtualObject {
public:
 virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,void*);
  
};
class O2 : public igVirtualObject {
public:
 virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v31(int);
  
};

struct LoaderRef {
    O1 *p;
    LoaderRef(O1 *object) : p(object) {}
    ~LoaderRef() {
        O1 *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
struct ReaderRef {
    O2 *p;
    ReaderRef(O2 *object) : p(object) {}
    ~ReaderRef() {
        O2 *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
struct PathText;
struct PathText {
    int text;
    PathText(int path) {
        int a;
        if (path == 0) {
            a = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int t = FUN_002eb010(0x10);
                if (t != 0) t = StringPool_Construct(t);
                DAT_00586f20[0] = t;
            }
            a = (int)StringPool_Intern(DAT_00586f20[0], path);
        }
        text = a;
    }
    ~PathText() {
        if (text != 0) {
            int *h = (int *)text - 2;
            int t = ((int *)text)[-1] - 1;
            ((int *)text)[-1] = t;
            if (t == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
};
extern "C" int FUN_00156340(G *, const PathText &);
extern "C" int Gap__Gfx__igPsx2Image__vfunc_39(G *arg0, int arg1)
{
  int var_s0 = 0;
  int s;
  s = FUN_0015ad50(arg1);
  if (s != 0) {
    if (strcmp(s, &DAT_004df5b8[0]) != 0) {
      if (strcmp(s, &DAT_004df5c0[0]) == 0) goto block_4;
      goto block_22;
    }
block_4:
    {
      igSmartPointer<O0> name((O0 *)FUN_002b9500(igObject_GetAllocator(arg0)));
      FUN_0030b3c0(name.p, arg1);
      LoaderRef loader((O1 *)FUN_00150060(igObject_GetAllocator(arg0)));
      var_s0 = loader.p->v21(name.p, arg0) & 0xFF;
      FUN_00156340(arg0, PathText(arg1));
    }
    return var_s0;
  }
block_22:
  if (s != 0) {
    if (strcmp(s, &DAT_004df5c8[0]) != 0) {
      if (strcmp(s, &DAT_004df5d0[0]) == 0) goto block_26;
    } else {
block_26:
      ReaderRef reader((O2 *)FUN_00150390(igObject_GetAllocator(arg0)));
      var_s0 = reader.p->v31(arg1) & 0xFF;
      if (var_s0 != 0) {
        arg0->v21(reader.p, 1);
      }
    }
  }
  return var_s0;
}
