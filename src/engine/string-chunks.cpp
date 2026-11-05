/* 0x0030c9b0 — byte-identical packed-storage initialization, finding #868.
 * ABI declarations below describe only observed fields and vtable position.
 * Reserved slots are not recovered method names; never instantiate this view.
 * MWCC reserves two leading slots, so 52 preceding methods place allocate at
 * byte 216. Host code uses the separate arena/memory-accessor reconstruction. */
class AllocatorSlot216 {
public:
    virtual void reserved0(); virtual void reserved1(); virtual void reserved2(); virtual void reserved3();
    virtual void reserved4(); virtual void reserved5(); virtual void reserved6(); virtual void reserved7();
    virtual void reserved8(); virtual void reserved9(); virtual void reserved10(); virtual void reserved11();
    virtual void reserved12(); virtual void reserved13(); virtual void reserved14(); virtual void reserved15();
    virtual void reserved16(); virtual void reserved17(); virtual void reserved18(); virtual void reserved19();
    virtual void reserved20(); virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
    virtual void reserved24(); virtual void reserved25(); virtual void reserved26(); virtual void reserved27();
    virtual void reserved28(); virtual void reserved29(); virtual void reserved30(); virtual void reserved31();
    virtual void reserved32(); virtual void reserved33(); virtual void reserved34(); virtual void reserved35();
    virtual void reserved36(); virtual void reserved37(); virtual void reserved38(); virtual void reserved39();
    virtual void reserved40(); virtual void reserved41(); virtual void reserved42(); virtual void reserved43();
    virtual void reserved44(); virtual void reserved45(); virtual void reserved46(); virtual void reserved47();
    virtual void reserved48(); virtual void reserved49(); virtual void reserved50(); virtual void reserved51();
    virtual int allocate_bytes(int);
};
struct StringChunkLayout {
    int table, next, previous, size, storage, end, head, largest;
    unsigned char empty;
};
typedef char StringChunkSizeCheck[sizeof(StringChunkLayout)==36 ? 1 : -1];
extern "C" void StringChunk_InitializeStorage(StringChunkLayout *chunk) {
    chunk->storage=((AllocatorSlot216 *)*(int *)((char *)*(int *)chunk->table+12))->allocate_bytes(chunk->size);
    chunk->head=chunk->storage+chunk->size;
    chunk->end=chunk->storage+chunk->size;
    {
        unsigned short *footer_end=(unsigned short *)chunk->head;
        footer_end[-1]=((unsigned)chunk->size)>>2;
        footer_end[-2]=0;
    }
}
