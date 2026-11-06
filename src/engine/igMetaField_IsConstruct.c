/* igMetaField slot +0xf0 (IsConstruct): whether the field's value is built by the field itself.
 * The base returns 0, so the generic object initialiser constructs a plain field's value;
 * igRefMetaField returns its declared `_construct` (+0x34) instead. */
int igMetaField_IsConstruct(void) {
    return 0;
}
