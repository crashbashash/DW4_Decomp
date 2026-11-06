/* 0x002fd070
 * igMetaField slot +0x84 (ZeroValue), base implementation: nothing to zero.
 * igRefMetaField overrides it (0x305500) to clear the reference slot at
 * `instance + _offset`; see the +0x84/+0x88 no-op defaults. */
void igMetaField_ZeroValue(void) {
}
