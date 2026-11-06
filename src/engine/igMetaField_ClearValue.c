/* 0x002fd080
 * igMetaField slot +0x88 (ClearValue), base implementation: nothing to clear.
 * igRefMetaField overrides it (0x305540) for its reference slot; the +0x84/+0x88
 * no-op defaults are recorded. */
void igMetaField_ClearValue(void) {
}
