/* 0x00300fa0
 * Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with
 * the igObject storage allocator (vtable slot 216, igObject_AllocateStorage),
 * strcpy into it and return the copy. */
int strcpy(int, int);  /* strcpy(dst, src): copies through the NUL, returns dst */
int strlen(int);  /* strlen(str) */
int igObject_AllocateStorage(int, int);

int igObject_DuplicateString(int self, int string) {
    int copy;

    copy = igObject_AllocateStorage(self, strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}
