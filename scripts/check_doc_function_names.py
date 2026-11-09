#!/usr/bin/env python3
"""check_doc_function_names.py -- fail when a document names a function it should not.

A method document, one on how to match or check code, names no function: an example goes stale when the
function is renamed or respelled, and nothing updates it. Every document under docs/ is a method document
unless config/doc-subjects.txt lists it as describing what a part of the game does. A subject document may
name what it describes, but each name must still exist in the symbol table, so a rename fails here until the
document catches up. Placeholders such as FUN_XXXXXXXX and Class__vfunc_NN are not names.

Each row of config/doc-subjects.txt is a document's path, then optionally a tab and the space-separated names
it may keep though the symbol table has dropped them: a document on what was removed has to say what it was.

Exit status: 0 clean, 1 findings.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SUBJECTS = os.path.join(ROOT, "config", "doc-subjects.txt")
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
DOCS = os.path.join(ROOT, "docs")
FUNCTION_NAME = re.compile(r"\b(?:thunk_)?FUN_[0-9a-f]{6,8}\b|\b\w+__vfunc_\d+(?:__[0-9a-f]{8})?\b")


def named_functions(text):
    return sorted(set(FUNCTION_NAME.findall(text)))


def load_subjects(path=SUBJECTS):
    """{document path: set of retired names it may keep}."""
    rows = {}
    with open(path) as fh:
        for line in fh:
            if line.strip() and not line.startswith("#"):
                doc, _, retired = line.rstrip("\n").partition("\t")
                rows[doc.strip()] = set(retired.split())
    return rows


def load_symbols(path=SYMBOLS):
    with open(path) as fh:
        return {line.split()[2] for line in fh if line[0] != "#" and len(line.split()) >= 3}


def check_text(rel, text, subjects, symbols):
    """Findings for one document."""
    names = named_functions(text)
    if rel not in subjects:
        return ["%s: a method document names %s (describe the shape, or list the document in "
                "config/doc-subjects.txt if it describes part of the game)" % (rel, name) for name in names]
    return ["%s: names %s, which the symbol table does not have (use its current name)" % (rel, name)
            for name in names if name not in symbols and name not in subjects[rel]]


def check_tree(root=ROOT, subjects=None, symbols=None):
    subjects = load_subjects() if subjects is None else subjects
    symbols = load_symbols() if symbols is None else symbols
    found = []
    seen = set()
    for dirpath, _dirs, files in os.walk(os.path.join(root, "docs")):
        for name in sorted(files):
            if name.endswith(".md"):
                path = os.path.join(dirpath, name)
                rel = os.path.relpath(path, root).replace(os.sep, "/")
                seen.add(rel)
                with open(path, errors="surrogateescape") as fh:
                    found.extend(check_text(rel, fh.read(), subjects, symbols))
    found.extend("%s: listed in config/doc-subjects.txt but missing" % rel for rel in sorted(set(subjects) - seen))
    return found


def main():
    found = check_tree()
    for line in found:
        print(line)
    print("check_doc_function_names: %s" % ("%d findings" % len(found) if found else "clean"))
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
