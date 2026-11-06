/* IgUnsignedShortArrayMetaField slot 2: forwards to igMetaField_Destruct, the destructor body
 * shared by the meta-field classes (releases the field's owned buffer when one is set, then runs
 * the igObject slot-0 base step). The receiver passes through in a0. */
int igMetaField_Destruct();

void Gap__Core__igUnsignedShortMetaField__vfunc_02(void) {
    igMetaField_Destruct();
}
