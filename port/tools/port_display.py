#!/usr/bin/env python3
"""Report the native desktop environment for launching the port.

Run the port from this same desktop session. The former remote-display harness
is retired; this helper no longer starts a compositor or VNC server.
"""
import json
import os
import sys


def main():
    names = ('XDG_RUNTIME_DIR', 'WAYLAND_DISPLAY', 'DISPLAY', 'XDG_SESSION_TYPE')
    env = {name: os.environ[name] for name in names if os.environ.get(name)}
    if not env.get('WAYLAND_DISPLAY') and not env.get('DISPLAY'):
        print('No desktop display found. Run from a graphical session, or use the port headlessly.',
              file=sys.stderr)
        return 1
    print(json.dumps(env, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
