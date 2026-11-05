/* 0x002fd040
 * igMetaField slot +0xa8 (ReleaseElements), base implementation: a plain field
 * owns no elements to release.  The memory-ref classes override it
 * (igMemoryRefMetaField_ReleaseElements 0x2fb0b0); finding #367. */
void igMetaField_ReleaseElements(void) {
}
