extern "C" {
void free(void *ptr);
void __dl__FPv(void *ptr) throw();
}

void __dl__FPv(void *ptr) throw() {
    free(ptr);
}
