/* 0x002fd230
 * igMetaField slot +0xf0 (IsConstruct): whether the field's value is built by
 * the field itself.  The base returns 0, so the generic object initialiser
 * constructs a plain field's value; igRefMetaField returns its declared
 * `_construct` (+0x34) instead (0x305cd0); finding #367. */
int igMetaField_IsConstruct(void) {
    return 0;
}
