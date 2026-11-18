void igMessageDefaultReceiver_MessageHandler(S_237940 *s) {
    if (s->obj) { PM pm = s->pm; (s->obj->*pm)(); }
}

