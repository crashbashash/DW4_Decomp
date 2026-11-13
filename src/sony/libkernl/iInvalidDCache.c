void _sceIDC(void *start, void *end);

/* InvalidDCache without the interrupt guard, for interrupt handlers: whole 64-byte lines. */
void iInvalidDCache(unsigned int start, unsigned int end) {
    _sceIDC((void *)(start & ~0x3F), (void *)(end & ~0x3F));
}
