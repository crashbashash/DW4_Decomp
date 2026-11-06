/* igMetaField reset hook, base implementation: an empty `jr ra`, so a reset request leaves the
 * value alone. Named IgnoreReset for that behaviour; it sits next to igMetaField_SetToDefault
 * 0x2fc580 and igMetaField_CopyDefaultToValue 0x2fc5a0, the bodies that do restore a default. */
void igMetaField_IgnoreReset(void) {
}
