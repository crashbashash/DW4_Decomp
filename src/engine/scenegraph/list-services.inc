/* Returns the string at `index` with a reference taken on it. The reference count is the word just
 * before the characters. */
igStringRef StringList_CopyRetained(igStringRefList *list, int index) {
    return ((igStringRef *)list->_data)[index];
}

