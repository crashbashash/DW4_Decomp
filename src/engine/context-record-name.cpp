/* igMemoryPoolContextInfo: lookup of a context record by name.
 *
 * A context holds 46 records of 144 bytes starting at +0x14, each with a 128-byte
 * inline name at +4 (docs/engine/context-lifecycle.md, findings #896 and #897; the
 * record view matches src/engine/context-slot-lifetime.cpp).  The view below
 * describes the observed 32-bit layout, not the original C++ spelling. */

/* Dispatch-only view: the dummies pad the vtable so that Lookup lands on slot 21,
 * the vtable offset 92 that FUN_002f2730 (vfunc_51) implements. */
class ContextVirtuals {
public:
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20();
    virtual void *Lookup(int index);  /* returns the allocator bound to record `index` */
};

struct NamedRecord {
    void *allocator;
    char name[128];
    void *descriptor;
    unsigned storageFlags, flags;
};
struct ContextRecords {
    char header[20];
    NamedRecord records[46];
};

extern "C" int igStrCmp(const char *, const char *);  /* 0 when the strings are equal */

/* 0x002f2830 (vtable offset 96)
 * Find the first of the 46 records whose name equals `name` and return what its
 * slot-21 lookup yields; null or empty names, and unknown names, give null. */
extern "C" void *Gap__Core__igMemoryPoolContextInfo__vfunc_52(ContextVirtuals *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!igStrCmp(((ContextRecords *)self)->records[i].name, name)) return self->Lookup(i);
        }
    }
    return 0;
}
