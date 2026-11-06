/* Lookup of a context record by name. A context holds 46 records of 144 bytes starting at +0x14,
 * each with a 128-byte inline name at +4. The view below describes the observed 32-bit layout, not
 * the original C++ spelling. */

/* Dispatch-only view: the dummies pad the vtable so that Lookup lands on slot 21 (vtable offset
 * 92). */
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

/* Finds the first of the 46 records whose name equals `name` and returns what its slot-21 lookup
 * yields; null or empty names, and unknown names, give null. */
extern "C" void *FUN_002f2830(ContextVirtuals *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!igStrCmp(((ContextRecords *)self)->records[i].name, name)) return self->Lookup(i);
        }
    }
    return 0;
}
