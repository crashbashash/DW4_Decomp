extern "C" {
void free(void *ptr);
void FUN_00100610(void *ptr) throw();
}

void FUN_00100610(void *ptr) throw() {
    free(ptr);
}
