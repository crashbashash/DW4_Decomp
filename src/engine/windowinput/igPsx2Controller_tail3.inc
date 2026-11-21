/* slot 36 of igPsx2Controller: set the _attachedWindow reference (+32). Reference-counted
 * assignment: retain the new object, release the old one (destroying it when its 23-bit count
 * reaches zero), then store the new one. */
void Gap__igPsx2Controller__vfunc_36(igPsx2Controller *self, igObject *window) {
    igObject *previousWindow;
    igObject::ref(window);
    previousWindow = (igObject *)(self->_attachedWindow);
    igObject::release(previousWindow);
    self->_attachedWindow = (int)window;
}

void Gap__igPsx2Controller__vfunc_33(igPsx2Controller *self, short arg1) {
    self->_id = arg1;
}

