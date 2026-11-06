#!/usr/bin/env python3
"""findings.py — read and check the findings register under docs/findings/.

The register is plain Markdown, edited by hand. A finding is an open hypothesis, a confirmed fact
with its evidence, or a refuted idea worth remembering; documents cite one as
`#N`. Finding N lives in the file for its block of 250 (`findings-0001-0250.md`, ...), in id order:

    <a id="fN"></a>
    ### #N · confirmed|unconfirmed|refuted

    **Where:** address or subject          (optional)

    The statement, in the present tense.

    **Notes:** ...                         (optional)

    **Evidence:** repository-relative files, commands, other findings   (required when confirmed)

Usage:
    findings.py show N [N ...]     print findings
    findings.py next               the next free id and the file it belongs in
    findings.py stats              counts by status
    findings.py check              structure, order, evidence, dates; every `#N` cited in the documents
                                   and source resolves; nothing cites a file only one machine has
                                   (exit 1 on a problem)
    findings.py link [--write]     turn `#N` citations in Markdown documents into links to the entry
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FOLDER = os.path.join(ROOT, "docs", "findings")
BLOCK = 250
STATUSES = ("confirmed", "unconfirmed", "refuted")
HEAD = re.compile(r"^### #(\d+) · (\w+)\s*$")
ANCHOR = re.compile(r'^<a id="f(\d+)"></a>\s*$')
DATE = re.compile(r"(?<![\w/_-])20\d\d-\d\d-\d\d(?![\w-])(?!\s\d\d-\d\d-\d\d)")
CITE = re.compile(r"(?<![\w&#/\[])#(\d{2,4})\b(?!\]\()")
PRIVATE = re.compile(r"(?<![A-Za-z_-])(?:scratch/|extras/|local/(?:captures|evidence|testing|tools|dumps|states|scripts|snapshots|hermes|"
                     r"reference|pcsx2|ps2-box-research|ps2sdk-ref|ghidra-projects)\b)|<scratch>")


def block_file(number):
    low = (number - 1) // BLOCK * BLOCK + 1
    return "findings-%04d-%04d.md" % (low, low + BLOCK - 1)


def files():
    return sorted(name for name in os.listdir(FOLDER) if re.match(r"findings-\d{4}-\d{4}\.md$", name))


def load():
    """[(number, status, file, text)] for every finding, in file order."""
    out = []
    for name in files():
        number = status = None
        body = []
        for line in open(os.path.join(FOLDER, name), encoding="utf-8").read().split("\n"):
            found = HEAD.match(line)
            if found:
                if number is not None:
                    out.append((number, status, name, "\n".join(body).strip()))
                number, status, body = int(found.group(1)), found.group(2), []
            elif number is not None and not ANCHOR.match(line):
                body.append(line)
        if number is not None:
            out.append((number, status, name, "\n".join(body).strip()))
    return out


def stats():
    """{"total": n, "confirmed": n, "unconfirmed": n, "refuted": n} (tools/progress.py reads this)."""
    out = dict.fromkeys(("total",) + STATUSES, 0)
    for _number, status, _name, _text in load():
        out["total"] += 1
        out[status] = out.get(status, 0) + 1
    return out


def tracked(*patterns):
    listed = subprocess.run(["git", "ls-files", "-co", "--exclude-standard", "--"] + list(patterns),
                            cwd=ROOT, capture_output=True, text=True).stdout.split("\n")
    return [name for name in listed if name and os.path.isfile(os.path.join(ROOT, name))]


def citations():
    """{number: [files]} for every `#N` in the documents and source outside the register."""
    out = {}
    names = tracked("*.md", "src", "include", "port/src", "port/include", "port/tools", "tools", "scripts", "config")
    for name in names:
        if name.startswith(("docs/findings/", "lua/", "src/third_party/", "port/third_party/")):
            continue
        if not name.endswith((".md", ".c", ".cpp", ".h", ".hpp", ".py", ".tsv", ".txt", ".sh")):
            continue
        try:
            text = open(os.path.join(ROOT, name), encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        for found in re.finditer(r"(?:finding|findings|Finding|Findings)[ :]*#(\d{1,4})\b|(?<![\w&#/])#(\d{3,4})\b", text):
            out.setdefault(int(found.group(1) or found.group(2)), []).append(name)
    return out


def check():
    problems = []
    seen = {}
    for name in files():
        text = open(os.path.join(FOLDER, name), encoding="utf-8").read()
        lines = text.split("\n")
        last = 0
        for index, line in enumerate(lines):
            found = HEAD.match(line)
            if not found:
                if line.startswith("### "):
                    problems.append("%s:%d: heading is not `### #N · status`" % (name, index + 1))
                continue
            number, status = int(found.group(1)), found.group(2)
            where = "%s #%d" % (name, number)
            if status not in STATUSES:
                problems.append("%s: status %r" % (where, status))
            if number in seen:
                problems.append("%s: also in %s" % (where, seen[number]))
            seen[number] = name
            if block_file(number) != name:
                problems.append("%s: belongs in %s" % (where, block_file(number)))
            if number <= last:
                problems.append("%s: not in id order" % where)
            last = number
            anchor = ANCHOR.match(lines[index - 1]) if index else None
            if not anchor or int(anchor.group(1)) != number:
                problems.append('%s: missing `<a id="f%d"></a>` on the line before' % (where, number))
    for number, status, name, text in load():
        where = "%s #%d" % (name, number)
        if status == "confirmed" and "**Evidence:**" not in text:
            problems.append("%s: confirmed without evidence" % where)
        if DATE.search(text):
            problems.append("%s: carries a date; state the finding as it stands" % where)
        if not text:
            problems.append("%s: empty" % where)
        if PRIVATE.search(text):
            problems.append("%s: cites a private file; nobody else can read it" % where)
    for number, names in sorted(citations().items()):
        if number not in seen and number >= 100:
            problems.append("#%d is cited in %s but is not in the register" % (number, ", ".join(sorted(set(names))[:3])))
    for name in tracked("*.md"):
        if name.startswith(("docs/findings/findings-", "lua/", "src/third_party/", "port/third_party/")):
            continue
        if PRIVATE.search(open(os.path.join(ROOT, name), encoding="utf-8", errors="replace").read()):
            problems.append("%s: cites a private file; nobody else can read it" % name)
    for line in problems[:60]:
        print("findings: " + line)
    if problems:
        print("findings: %d problem(s)" % len(problems))
        return 1
    totals = stats()
    print("findings: %d entries in %d files (%d confirmed, %d unconfirmed, %d refuted); every citation resolves"
          % (totals["total"], len(files()), totals["confirmed"], totals["unconfirmed"], totals["refuted"]))
    return 0


def link(write):
    """Make `#N` in Markdown documents a link to the entry. Code spans, code blocks and existing links stay."""
    known = {number for number, _status, _name, _text in load()}
    changed = 0
    for name in tracked("*.md"):
        if name.startswith(("docs/findings/", "lua/", "src/third_party/", "port/third_party/")):
            continue
        path = os.path.join(ROOT, name)
        text = open(path, encoding="utf-8").read()
        if re.search(r"(?i)generated by|do not (?:hand-)?edit", text[:800]):
            continue                        # a generated page is its generator's text; linking it would make it stale
        base = os.path.relpath(FOLDER, os.path.dirname(path))
        out, fence = [], False

        def replace(found):
            number = int(found.group(1))
            if number not in known:
                return found.group(0)
            return "[#%d](%s/%s#f%d)" % (number, base, block_file(number), number)

        for line in text.split("\n"):
            if line.lstrip().startswith("```"):
                fence = not fence
            if fence or line.startswith("    ") and not line.lstrip().startswith(("-", "*", "|")):
                out.append(line)
                continue
            # leave inline code and existing links alone
            parts = re.split(r"(`[^`]*`|\[[^\]]*\]\([^)]*\))", line)
            out.append("".join(part if index % 2 else CITE.sub(replace, part) for index, part in enumerate(parts)))
        new = "\n".join(out)
        if new != text:
            changed += 1
            if write:
                open(path, "w", encoding="utf-8").write(new)
    print("findings: %d document(s) %s" % (changed, "linked" if write else "would change (run with --write)"))
    return 0


def main(argv):
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0
    command, rest = argv[0], argv[1:]
    if command == "show":
        entries = {number: (status, name, text) for number, status, name, text in load()}
        for raw in rest:
            number = int(raw.lstrip("#"))
            if number not in entries:
                print("#%d is not in the register" % number)
                continue
            status, name, text = entries[number]
            print("#%d · %s  (docs/findings/%s)\n%s\n" % (number, status, name, text))
        return 0
    if command == "next":
        number = max(number for number, _status, _name, _text in load()) + 1
        print("#%d goes at the end of docs/findings/%s" % (number, block_file(number)))
        return 0
    if command == "stats":
        totals = stats()
        print("%d findings: %d confirmed, %d unconfirmed, %d refuted"
              % (totals["total"], totals["confirmed"], totals["unconfirmed"], totals["refuted"]))
        return 0
    if command == "check":
        return check()
    if command == "link":
        return link("--write" in rest)
    print(__doc__)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
