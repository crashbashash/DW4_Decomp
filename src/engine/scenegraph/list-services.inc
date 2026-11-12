/* Returns the string at `index` with a reference taken on it. The reference count is the word just
 * before the characters. */
RetainedString StringList_CopyRetained(igStringRefList *list, int index) {
    return RetainedString(((char **)list->_data)[index]);
}

