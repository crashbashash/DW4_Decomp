/* CRI's mcp_not.c: memory copies with a transfer unit in the name (plain, 4, 8, 32 bytes) and their
 * "Sq" variants. Without the vector hardware (the "not" build) all of them are memcpy. */
void *memcpy(void *dst, const void *src, unsigned int n);

void MEM_Copy(void *dst, void *src, int n);
void MEM_Copy4(void *dst, void *src, int n);
void MEM_Copy8(void *dst, void *src, int n);
void MEM_Copy32(void *dst, void *src, int n);

void MEM_Copy(void *dst, void *src, int n)
{
    memcpy(dst, src, n);
}

void MEM_Copy4(void *dst, void *src, int n)
{
    memcpy(dst, src, n);
}

void MEM_Copy8(void *dst, void *src, int n)
{
    memcpy(dst, src, n);
}

void MEM_Copy32(void *dst, void *src, int n)
{
    memcpy(dst, src, n);
}

void MEM_CopySq(void *dst, void *src, int n)
{
    MEM_Copy(dst, src, n);
}

void MEM_CopySq4(void *dst, void *src, int n)
{
    MEM_Copy4(dst, src, n);
}

void MEM_CopySq8(void *dst, void *src, int n)
{
    MEM_Copy8(dst, src, n);
}

void MEM_CopySq32(void *dst, void *src, int n)
{
    MEM_Copy32(dst, src, n);
}
