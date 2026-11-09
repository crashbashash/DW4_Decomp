typedef struct HashBinding {
    char pad0[40];
    short slot;
    unsigned short index : 12;
    unsigned char c4 : 1;
    unsigned char c5 : 1;
    unsigned char c6 : 1;
    unsigned char exported : 1;
} HashBinding;

typedef struct TypeSig {
    int words[3];
} TypeSig;

void *Memory_AllocateBufferDirect(int size, void *allocator);
TypeSig *FUN_0023c920(TypeSig *sig, char **names, unsigned int code);
HashBinding *FUN_0023e160(void *mem, void *function, int slot, char *name, TypeSig *result, int owner, int exported, int argCount);
extern void *DAT_0056de30;

void FUN_0023f4f0(int owner, void *method, void *function, char **names, int count, unsigned int *codes, HashBinding **slots)
{
    int i;
    unsigned int code;
    unsigned int argCount;
    HashBinding *binding;
    TypeSig *args;
    unsigned int j;
    void *handler;
    TypeSig result;

    for (i = 0; i < count; i++) {
        code = *codes++;
        argCount = (code >> 8) & 31;
        binding = Memory_AllocateBufferDirect(argCount * 12 + 44, DAT_0056de30);
        if (binding != 0) {
            handler = ((code >> 30) & 1) ? method : function;
            binding = FUN_0023e160(binding, handler, code & 0xff, names[(code >> 13) & 0x1ffff],
                                   FUN_0023c920(&result, names, *codes++), owner, ((code >> 31) & 1) != 0, argCount);
        }
        if (slots != 0 && binding->exported) slots[binding->slot] = binding;
        args = (TypeSig *)(binding + 1);
        for (j = 0; j < argCount; j++) {
            TypeSig *arg = &args[j];
            if (arg != 0) FUN_0023c920(arg, names, *codes++);
        }
    }
}
