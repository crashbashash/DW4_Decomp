void *memcpy(void *, const void *, unsigned int);
void *thunk_memcpy(void *d, const void *s, unsigned int n) {
    return memcpy(d, s, n);
}
