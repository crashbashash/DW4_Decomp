#!/usr/bin/env python3
"""check_host_details.py -- fail when text that identifies a developer's machine or account enters the repository.

The hard rules and their rationale are in docs/host-details-policy.md. This tool enforces them mechanically:

  scripts/check_host_details.py --tree              every tracked text file in the working tree
  scripts/check_host_details.py --staged            only the lines being added to the index (pre-commit hook)
  scripts/check_host_details.py --msg FILE          a commit message (commit-msg hook)
  scripts/check_host_details.py --range BASE..HEAD  added lines and commit messages in a range (CI)

Patterns are generic on purpose (any home directory, any GPU/CPU model, any third-party controller brand, ...) so this file
never has to name the thing it forbids. Exceptions go in scripts/host_details_allow.txt, one per line:
    <path-glob><TAB><regex that the matched text must match>
Exit status: 0 clean, 1 findings, 2 usage or environment error.
"""
import argparse, fnmatch, os, re, subprocess, sys

RULES = [
    ("home-path", r"(?:/home/(?!(?:example|user|runner|you|name|me)\b)[A-Za-z0-9._-]+/|/Users/(?!(?:example|user|runner|you|name|me|Shared)\b)[A-Za-z0-9._-]+/|[A-Za-z]:\\Users\\(?!(?:example|user|you|name|me|Public)\b)[^\\\s]+)",
     "an absolute home directory names the account; use a repository-relative path, ../local/, <repo> or ~/"),
    ("workspace-path", r"(?<![A-Za-z0-9_.-])/workspace/",
     "a container/workspace absolute path; use a repository-relative path"),
    ("gpu-model", r"\b(?:(?:GeForce\s+)?(?:RTX|GTX)\s?\d{3,4}(?:\s?(?:Ti|SUPER))?|RX\s?\d{3,4}(?:\s?XT)?|Radeon\s+(?:RX|Pro|VII|HD|R\d)\b[^\n]{0,12}|Arc\s+[AB]\d{3}|Iris\s+Xe)\b",
     "a specific graphics card model; write 'a desktop GPU' (vendor-level is fine)"),
    ("cpu-model", r"\b(?:Ryzen\s+[3579]?\s?\d{3,5}[A-Za-z0-9]*|Core\s+i[3579]-\d{3,5}[A-Za-z]*|Threadripper|Xeon|Apple\s+M[1-4]\b)",
     "a specific processor model; write 'a desktop CPU'"),
    ("controller-brand", r"\b(?:8BitDo|Logitech|Razer|Joy-?Con|Switch\s+Pro\s+Controller|DualSense|Stadia\s+Controller)\b",
     "a third-party controller brand/model; write 'a physical gamepad'"),
    ("driver-version", r"\b(?:Mesa\s+\d+\.\d+|LLVM\s+\d+\.\d+|DRM\s+\d+\.\d+|Linux\s+(?:kernel\s+)?\d+\.\d+|kernel\s+\d+\.\d+\.\d+|NVIDIA\s+(?:driver\s+)?\d{3}\.\d+)",
     "driver/kernel/toolchain version of the host; drop the number"),
    ("device-node", r"(?:/dev/dri/(?:card|renderD)\d+|/sys/class/drm/card\d|\brenderD\d{3}\b|\bPCI\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{4}\b|\b(?:10de|1002|8086):[0-9a-f]{4}\b)",
     "a device node or PCI id of the host"),
    ("host-description", r"\b(?:CachyOS|Arch\s+Linux|Manjaro|Fedora\s+\d+|Ubuntu\s+\d{2}\.\d{2}|Debian\s+\d+|NixOS|Hyprland|KDE\s+Plasma\s+\d|GNOME\s+\d+)\b",
     "the developer's distribution or desktop; describe requirements, not the machine"),
    ("personal-email", r"[A-Za-z0-9._%+-]+@(?:gmail|googlemail|outlook|hotmail|live|yahoo|icloud|proton(?:mail)?|pm)\.(?:com|me)\b",
     "a personal e-mail address"),
    ("private-ip", r"\b(?:10\.\d{1,3}|192\.168|172\.(?:1[6-9]|2\d|3[01]))\.\d{1,3}\.\d{1,3}\b",
     "a private network address"),
    ("secret", r"(?:-----BEGIN (?:[A-Z]+ )?PRIVATE KEY-----|\bgh[pousr]_[A-Za-z0-9]{36,}\b|\bAKIA[0-9A-Z]{16}\b|\bxox[baprs]-[A-Za-z0-9-]{10,}\b)",
     "a credential"),
    # Emulator session details: a private PINE slot (a 4-5 digit port number), a per-user runtime socket
    # directory, or the number of the X display one machine happens to run the emulator on.
    # (a bare "slot NNNN" with four digits is left alone: vtable slot indices reach four digits)
    ("emulator-slot", r"(?:\bPINE\s+slots?[\s:=-]*\d{4,5}\b|\bslots?[\s:=-]*\d{5}\b|--slot[\s=]+\d{4,5}\b|\bslot-\d{4,5}\b)",
     "a private emulator socket slot; write 'the configured PINE slot' and take the number from the environment or a config file"),
    ("runtime-socket", r"/run/user/(?:\d+|%d|\$\w+|\$\{[^}]*\}|<[^>]*>)/",
     "a per-user runtime directory; take XDG_RUNTIME_DIR or an env var instead of spelling the path"),
    ("x-display", r"(?:\bDISPLAY=:\d+\b|\b(?:Xwayland|Xvfb|Xephyr|xinit|startx)\s+:\d+\b|\b[Dd]isplay\s+:\d+\b)",
     "the X display number of one machine; say 'an X11 or XWayland display' and take the number from DISPLAY"),
    # Install and scratch locations of one machine.  /opt/<x> is where *this* host put a tool; a session- or
    # account-stamped /tmp path (an agent scratchpad, a uid-stamped directory) names a session that no reader
    # has.  Plain `/tmp/<file>` in a command example is generic and is not flagged here, but the findings
    # register (docs/findings/) holds evidence and is held to the stricter DB_RULES below.
    ("opt-path", r"(?<![A-Za-z0-9_.-])/opt/[A-Za-z0-9._-]+",
     "an install location of one machine; name the tool and the env var or config key that locates it"),
    ("tmp-session-path", r"/tmp/(?:[A-Za-z0-9._-]*(?:claude|codex|agent|session)[A-Za-z0-9._-]*|[A-Za-z0-9._-]*-home-[A-Za-z0-9._-]*|[A-Za-z]+-\d{4,})(?:/|\b)",
     "a session- or account-stamped scratch path; use ../scratch/ or <scratch>"),
    # Hardware words beyond a model number: the host's processor vendor, and GPU families/architectures.
    ("cpu-vendor", r"\b(?:[Aa]ctual\s+)?(?:AMD|Intel|ARM|Apple)\s+CPU(?:\s*/\s*GPU)?\b",
     "the vendor of the host's processor says nothing a reader needs; write 'a desktop CPU' (or 'the CPU and GPU checks')"),
    ("gpu-family", r"\b(?:RDNA\s?\d|GCN\s?\d|Navi\s?\d{2}|Vega\s?\d{1,2}|Polaris\s?\d{2}|GeForce\s+\d{3,4}|Quadro\s+[A-Z]*\d{3,4}|Ada\s+Lovelace|Ampere\s+GPU|Turing\s+GPU|Adreno\s+\d{3}|Mali-[GT]\d{2,3})\b",
     "a GPU family or architecture of the host; write 'a desktop GPU' (vendor-level is fine)"),
]
COMPILED = [(n, re.compile(p), h) for n, p, h in RULES]
# The findings register records evidence, which must be reproducible from the repository: any /tmp or /opt
# path there is a machine's scratch or install location, not an artifact a reader can open.
DB_RULES = [
    ("db-scratch-path", r"(?<![A-Za-z0-9_.-])/(?:tmp|opt|var/tmp)/[A-Za-z0-9._-]+",
     "findings cite repository-relative paths (or ../scratch/, ../local/, ../extras/); a /tmp or /opt path is one machine's"),
]
DB_COMPILED = [(n, re.compile(p), h) for n, p, h in DB_RULES]
REGISTER = "docs/findings/"       # the findings register: evidence text, held to DB_RULES as well
ALLOW_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "host_details_allow.txt")
MAX_BYTES = 8 * 1024 * 1024
SELF = "scripts/check_host_details.py"


def load_allow():
    out = []
    if os.path.exists(ALLOW_FILE):
        for line in open(ALLOW_FILE, encoding="utf-8"):
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            glob, _, rx = line.partition("\t")
            out.append((glob, re.compile(rx or ".*")))
    return out


ALLOW = load_allow()


def allowed(path, text):
    return any(fnmatch.fnmatch(path, g) and rx.search(text) for g, rx in ALLOW)


def scan_text(path, text, first_line=1, only_lines=None, rules=COMPILED):
    """Yield (path, line, rule, excerpt, hint) for each violation."""
    if path in (SELF, "docs/host-details-policy.md", "testing/test_check_host_details.py"):
        return
    for i, line in enumerate(text.split("\n")):
        no = first_line + i
        if only_lines is not None and no not in only_lines:
            continue
        for name, rx, hint in rules:
            for m in rx.finditer(line):
                if allowed(path, m.group(0)):
                    continue
                yield (path, no, name, m.group(0)[:60], hint)


def git(*args, check=True):
    r = subprocess.run(["git", *args], capture_output=True)
    if check and r.returncode:
        sys.stderr.write(r.stderr.decode("utf-8", "replace"))
        sys.exit(2)
    return r.stdout


def scan_tree():
    for f in git("ls-files", "-z").split(b"\0"):
        if not f:
            continue
        p = f.decode()
        try:
            if os.path.getsize(p) > MAX_BYTES:
                continue
            raw = open(p, "rb").read()
        except (FileNotFoundError, IsADirectoryError, OSError):
            continue
        if b"\0" in raw[:8000]:
            continue
        yield from scan_text(p, raw.decode("utf-8", "replace"))
        if p.startswith(REGISTER):
            yield from scan_text(p, raw.decode("utf-8", "replace"), rules=DB_COMPILED)




def added_lines(diff_args):
    """Parse a unified diff (zero context) into {path: {line numbers}} plus the text of those lines."""
    out = git("diff", "--no-color", "--no-ext-diff", "-U0", "--diff-filter=AMR", *diff_args).decode("utf-8", "replace")
    path, no, res = None, 0, {}
    for line in out.split("\n"):
        if line.startswith("+++ "):
            path = line[6:] if line.startswith("+++ b/") else None
        elif line.startswith("@@") and path:
            m = re.match(r"@@ -\d+(?:,\d+)? \+(\d+)(?:,\d+)? @@", line)
            no = int(m.group(1)) if m else 0
        elif line.startswith("+") and not line.startswith("+++") and path:
            res.setdefault(path, []).append((no, line[1:]))
            no += 1
    return res


def scan_added(diff_args):
    for path, lines in added_lines(diff_args).items():
        for no, text in lines:
            yield from scan_text(path, text, first_line=no)


def scan_messages(rev_range):
    out = git("log", "--format=%H%x00%B%x01", rev_range).decode("utf-8", "replace")
    for rec in out.split("\x01"):
        if not rec.strip("\n"):
            continue
        sha, _, body = rec.lstrip("\n").partition("\0")
        yield from scan_text("commit %s" % sha[:9], body)


def report(hits):
    n = 0
    for path, no, rule, excerpt, hint in hits:
        n += 1
        print("%s:%d: [%s] %r -- %s" % (path, no, rule, excerpt, hint))
    return n


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--tree", action="store_true")
    g.add_argument("--staged", action="store_true")
    g.add_argument("--msg", metavar="FILE")
    g.add_argument("--range", metavar="BASE..HEAD")
    a = ap.parse_args(argv)
    if a.tree:
        hits = list(scan_tree())
    elif a.staged:
        hits = list(scan_added(["--cached"]))
    elif a.msg:
        hits = list(scan_text("commit message", open(a.msg, encoding="utf-8", errors="replace").read()))
    else:
        hits = list(scan_added([a.range])) + list(scan_messages(a.range))
    n = report(hits)
    if n:
        sys.stderr.write("\ncheck_host_details: %d finding(s). Remove the detail or, if it is a deliberate fixture, add an exception to\n"
                         "scripts/host_details_allow.txt. Rules: docs/host-details-policy.md\n" % n)
        return 1
    print("check_host_details: clean")
    return 0


if __name__ == "__main__":
    sys.exit(main())
