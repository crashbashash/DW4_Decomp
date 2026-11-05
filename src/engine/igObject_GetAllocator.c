int igAllocator_ResolveEncodedIndex(int);

int igObject_GetAllocator(int a0) {
    return igAllocator_ResolveEncodedIndex(*(unsigned char *)((char *)a0 + 7));
}
