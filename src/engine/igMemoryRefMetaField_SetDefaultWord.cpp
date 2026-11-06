/* Word-default wrapper of the memory-reference metafield: copy the word into a temporary cell and
 * call the virtual method at vtable offset 140 with the cell's address (not the word itself) as
 * the default pointer. */
extern "C" {

void igMemoryRefMetaField_SetDefaultWord(void **self, int defaultWord);
}
/* The metafield's vtable: 33 unnamed padding slots, then the call at offset 140. */
class MemoryRefMetaFieldVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int setDefault(int); };
void igMemoryRefMetaField_SetDefaultWord(void **self, int defaultWord) {
    int defaultCell;

    defaultCell = defaultWord;
    ((MemoryRefMetaFieldVtable *)(self))->setDefault((int)(&defaultCell));
}
