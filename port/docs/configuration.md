# Options configuration

The native front end loads `config.ini` before initializing the recovered title
controller. Closing Options with Return or Circle commits Dungeon camera and Light
through the controller's existing close transition, then persists their confirmed
values. Closing the application while Options is still open leaves the previous
configuration intact. The Main Lobby adapter applies the confirmed Light setting
to both world lighting and named texture selection on arrival; see [retail recovery and
validation](lobby-rendering.md#hardsoft-option). Dungeon camera
remains retained for its eventual gameplay consumer.

## Location

Linux and native Steam Deck use `$XDG_CONFIG_HOME/dw4/config.ini`, falling back to
`~/.config/dw4/config.ini` when the variable is empty, unset or relative. If HOME
is unavailable, resolve the account home through the system user database.
Windows uses the redirected Local AppData Known Folder, then `DW4/config/config.ini`.

`dw4 --portable` explicitly selects `userdata/config/config.ini` beside the
executable, independent of the working directory. Normal storage remains the
default, including for download-and-run builds. Configuration directories are
created on first use. Boot prints the selected configuration filename.
This implementation resolves configuration only: native saves, asset extraction,
mod overrides, caches and state directories remain separate future work.

## INI schema and parser

A fresh configuration contains the original power-on defaults:

```ini
[options]
camera=near
light=hard
```

| Setting | Accepted values | Default |
| --- | --- | --- |
| `options.camera` | `near`, `far` | `near` |
| `options.light` | `soft`, `hard` | `hard` |

Section names, keys and values are case-sensitive. Spaces and tabs around keys
and values are allowed. `;` and `#` start full-line comments, or inline comments
when separated from a value by whitespace. Values are unquoted tokens; there is
no escaping syntax for these two settings. UTF-8 BOMs and CRLF files are accepted.
Repeated sections are allowed; the last occurrence of a known key wins. Invalid
known values warn with the setting and filename and use that setting's default;
other valid settings remain active. Unknown entries and malformed unknown lines
are retained without interpretation. Embedded NUL bytes fail loading rather than
silently truncating the document. User edits are loaded on the next launch.

## Writes and failures

Only settings changed since loading or the last successful write are updated.
The writer rereads the file before saving, retaining external edits to untouched
settings, comments, unknown entries, whitespace and existing line endings. All
occurrences of a changed duplicate key receive the new value so none can shadow
it. Missing changed keys are appended in an `[options]` section. Appended lines
use LF; existing lines keep their original endings. An unchanged configuration is
not rewritten. Invalid unchanged settings remain on disk until changed in-game.

Writes use a temporary sibling file and replace the destination only after the
write closes successfully. Linux flushes file contents before replacement;
Windows requests replacement with write-through. Failed writes retain the previous
file and confirmed in-memory settings. Windowed failures show the filename and
Retry/Back. Back cancels the file operation; closing Options again retries pending
changes. An unreadable configuration stops startup with Retry/Back, with Back
exiting. Headless failures report diagnostics without opening dialogs. They stop
startup on load failure and retain in-memory settings on write failure.

This is not a guarantee against power-loss recovery on every filesystem, nor a
multi-process configuration merge: simultaneous edits to the same changed key are
replaced by the in-game value. Native save transactions are not implemented here.

## Validation

`make check-options` is asset-independent and checks round trips, selective
updates, annotations, BOM/CRLF, long lines, missing keys, duplicate keys, invalid
values, read/write errors and retry, XDG fallbacks, Unicode/space paths, and
portable storage after changing working directories.

`make check-options-menu` uses the original assets to drive the recovered Options
controller across separate host processes. It verifies no write before close,
both settings persisting after close, relaunch loading, and external edits with
comments/unknown sections retained. Existing front-end checks use isolated
configuration directories to avoid changing the operator's settings.

Linux checks pass locally. Redirected Windows folders, Windows Unicode paths,
Windows replacement guarantees, physical Steam Deck and interactive Retry/Back
still require platform validation. Bindings and future host display settings are
not yet part of this schema.
