/* CRI's memory copies (src/cri/mcpnot.c): a transfer unit in the name (plain, 4, 8, 32 bytes) and the
 * "Sq" variants. */
#ifndef DW4_CRI_MCP_H
#define DW4_CRI_MCP_H

void MEM_Copy(void *dst, void *src, int n);
void MEM_Copy4(void *dst, void *src, int n);
void MEM_Copy8(void *dst, void *src, int n);
void MEM_Copy32(void *dst, void *src, int n);
void MEM_CopySq(void *dst, void *src, int n);
void MEM_CopySq4(void *dst, void *src, int n);
void MEM_CopySq8(void *dst, void *src, int n);
void MEM_CopySq32(void *dst, void *src, int n);

#endif
