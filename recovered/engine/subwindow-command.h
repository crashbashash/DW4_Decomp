#ifndef DW4_RECOVERED_SUBWINDOW_COMMAND_H
#define DW4_RECOVERED_SUBWINDOW_COMMAND_H
#include "messenger-results.h"
/* Complete SUBWND receiver at3d60e0. Supply a private400-byte guest frame;
 * name references, text buffers and preview vectors remain guest-addressed.
 * Enumeration, formatting, messaging, records and preparation are callbacks.
 * This is a behavioral reference, not matching source or a host menu. */
uint64_t dw4_subwindow_command(const Dw4MessengerResultsApi *,const uint64_t args[8],uint32_t scratch);
#endif
