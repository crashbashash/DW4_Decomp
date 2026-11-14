#!/usr/bin/env python3
"""levers.py — the "Causes found" of docs/engine/understanding-shapes.md as a lever catalogue.

Each entry of that section (a top-level `- **Title.**` bullet under a `###` heading, with its
*Symptom:*, *Cause:*, *Spelling:* and *Unit:* parts) becomes one JSON line of data/levers.jsonl:
`id`, `section`, `compiler` (from the heading's `(b52)`/`(EE GCC)`), `title`, `symptom`, `cause`,
`spelling`, `units` (the `src/` paths its Unit names), `unit_text`, `addresses`, `notes` (other
labelled parts such as *Reading it:*), `confidence` and `lines` (the entry's first and last line). An
entry written as prose has its text after the title as `symptom`. `confidence` is `open` for an entry
titled "Open: …", `proven` when it cites a Unit (the spelling reproduced retail there), else `uncited`.
The document is the source: data/levers.jsonl is generated, never edited, and `make hygiene` runs
`--check`.

The catalogue format follows decomp-triage's levers.jsonl (CC0,
https://github.com/KakarottoCake/decomp-triage); the code is this project's own.

  python3 tools/levers.py                              # entries per section
  python3 tools/levers.py --symptom "addu v0,v0,zero"  # entries ranked by the words of a symptom
  python3 tools/levers.py --section "Delay slots"      # every entry of the matching sections
  python3 tools/levers.py --symptom "stack slot" --format prompt   # a compact block to paste to an agent
  python3 tools/levers.py --write                      # regenerate data/levers.jsonl after editing the doc
  python3 tools/levers.py --check                      # exit 1 when data/levers.jsonl is stale
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
DOC = "docs/engine/understanding-shapes.md"
OUT = "data/levers.jsonl"

_FIELD = re.compile(r"\*([A-Z][A-Za-z ,]{0,40}):\*")
_TITLE = re.compile(r"^- \*\*(.+?)\*\*")
_ADDRESS = re.compile(r"\b0x[0-9a-fA-F]{5,8}\b")
_PATH = re.compile(r"`(src/[^`\s]*)`")
_STOP = {"a", "an", "the", "is", "are", "of", "to", "in", "on", "and", "its", "it", "by", "as", "for",
         "with", "one", "that", "at", "be", "or", "from", "into"}


def _slug(text, words=None):
    tokens = re.findall(r"[a-z0-9]+", re.sub(r"'s\b", "", text.lower()).replace("`", ""))
    if words:
        tokens = [t for t in tokens if t not in _STOP][:words]
    return "-".join(tokens)


def _flatten(lines):
    """An entry's lines as one string: sub-bullet markers dropped, whitespace collapsed."""
    return " ".join(re.sub(r"^\s*-\s+", "", line).strip() for line in lines if line.strip())


def _entry(section, number, lines):
    title_m = _TITLE.match(lines[0])
    title = title_m.group(1).strip()
    text = _flatten([lines[0][title_m.end():]] + lines[1:])
    parts = _FIELD.split(text)
    record = {"summary": parts[0].strip()}
    fields = {}
    for label, body in zip(parts[1::2], parts[2::2]):
        fields.setdefault(label.strip(), []).append(body.strip())
    def take(*labels):
        found = [body for label, bodies in fields.items() for body in bodies
                 if any(label == want or label.startswith(want + ",") for want in labels)]
        return " / ".join(found)
    symptom = take("Symptom") or record["summary"]
    unit_text = take("Unit", "Units")
    notes = ["%s: %s" % (label, body) for label, bodies in fields.items()
             if not re.match(r"(Symptom|Cause|Spelling|Units?)\b", label) for body in bodies]
    if record["summary"] and symptom != record["summary"]:
        notes.insert(0, record["summary"])
    units = sorted(set(_PATH.findall(unit_text)))
    compiler = re.search(r"\(([^)]*)\)\s*$", section)
    if title.startswith("Open"):
        confidence = "open"
    elif unit_text:
        confidence = "proven"
    else:
        confidence = "uncited"
    return {
        "section": section,
        "compiler": compiler.group(1) if compiler else "",
        "title": title,
        "symptom": symptom,
        "cause": take("Cause"),
        "spelling": take("Spelling"),
        "units": units,
        "unit_text": unit_text,
        "addresses": sorted(set(a.lower() for a in _ADDRESS.findall(" ".join(lines)))),
        "notes": notes,
        "confidence": confidence,
        "lines": [number, number + len(lines) - 1 - next(i for i, l in enumerate(reversed(lines)) if l.strip())],
    }


def parse(text):
    """The entries of the document's "Causes found" section, in document order, with unique ids."""
    entries, section, current, inside = [], None, None, False
    def close():
        if current:
            entries.append(_entry(section, current[0], current[1]))
    for number, line in enumerate(text.splitlines(), 1):
        if line.startswith("## "):
            close()
            current = None
            inside = line[3:].strip() == "Causes found"
            continue
        if not inside:
            continue
        if line.startswith("### "):
            close()
            current, section = None, line[4:].strip()
        elif _TITLE.match(line) and section:
            close()
            current = (number, [line])
        elif current and (line.startswith(" ") or not line.strip()):
            current[1].append(line)
        elif line.strip():
            close()
            current = None
    close()
    seen = {}
    for entry in entries:
        base = "%s/%s" % (_slug(entry["section"]), _slug(re.sub(r"^Open:\s*", "open ", entry["title"]), 6))
        seen[base] = seen.get(base, 0) + 1
        entry["id"] = base if seen[base] == 1 else "%s-%d" % (base, seen[base])
    keys = ("id", "section", "compiler", "title", "symptom", "cause", "spelling", "units", "unit_text",
            "addresses", "notes", "confidence", "lines")
    return [{key: entry[key] for key in keys} for entry in entries]


def render(entries):
    return "".join(json.dumps(entry, ensure_ascii=False) + "\n" for entry in entries)


def load(root=ROOT):
    with open(os.path.join(root, DOC), encoding="utf-8") as fh:
        return parse(fh.read())


def search(entries, query):
    """Entries ranked by how many words of `query` they contain: symptom and title first, then the
    cause, spelling and notes. A word of the query is matched as a case-insensitive substring, so a
    mnemonic, a register or an operand sequence such as `addu v0,v0,zero` finds the entry quoting it."""
    terms = [t for t in re.split(r"[\s;]+", query.lower()) if t and t not in _STOP]
    ranked = []
    for entry in entries:
        weighted = ((3, entry["symptom"] + " " + entry["title"]),
                    (1, " ".join([entry["cause"], entry["spelling"]] + entry["notes"])))
        hits, score = 0, 0
        for term in terms:
            weights = [w for w, text in weighted if term in text.lower()]
            if weights:
                hits += 1
                score += max(weights)
        if hits:
            ranked.append((-hits, -score, entry["lines"][0], entry))
    ranked.sort(key=lambda row: row[:3])
    return [row[3] for row in ranked]


def format_text(entry):
    out = ["%s  [%s] %s:%d-%d" % ((entry["id"], entry["confidence"], DOC) + tuple(entry["lines"])),
           "  " + entry["title"]]
    for key in ("symptom", "cause", "spelling"):
        if entry[key]:
            out.append("  %s: %s" % (key, entry[key]))
    out.extend("  note: " + note for note in entry["notes"])
    if entry["unit_text"]:
        out.append("  unit: " + entry["unit_text"])
    return "\n".join(out)


def format_prompt(entries):
    """One block an agent can be handed: each lever as title, symptom, spelling and where it was proven.
    The cause is left out for length; the line range leads back to it."""
    out = ["Levers from %s (\"Causes found\"). A lever is a hypothesis for this function until it" % DOC,
           "reproduces retail here; read the cause at the cited line before applying one."]
    for entry in entries:
        out.append("- [%s, %s%s] %s" % (entry["id"], entry["confidence"],
                                       ", " + entry["compiler"] if entry["compiler"] else "", entry["title"]))
        if entry["symptom"]:
            out.append("  Symptom: " + entry["symptom"])
        if entry["spelling"]:
            out.append("  Spelling: " + entry["spelling"])
        if entry["unit_text"]:
            out.append("  Unit: " + entry["unit_text"])
        out.append("  Source: %s:%d-%d" % ((DOC,) + tuple(entry["lines"])))
    return "\n".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--symptom", help="rank entries by the words of this text")
    ap.add_argument("--section", help="entries of the sections whose heading contains this text")
    ap.add_argument("--id", help="the entry with this id")
    ap.add_argument("--confidence", choices=("proven", "open", "uncited"), help="only entries of this confidence")
    ap.add_argument("--limit", type=int, default=5, help="at most this many --symptom results (0: all)")
    ap.add_argument("--format", choices=("text", "prompt", "json"), default="text")
    ap.add_argument("--write", action="store_true", help="regenerate %s from %s" % (OUT, DOC))
    ap.add_argument("--check", action="store_true", help="exit 1 when %s is not what %s generates" % (OUT, DOC))
    args = ap.parse_args(argv)

    entries = load()
    out_path = os.path.join(ROOT, OUT)
    if args.write or args.check:
        want = render(entries)
        have = open(out_path, encoding="utf-8").read() if os.path.exists(out_path) else None
        if args.check:
            if have != want:
                print("levers: %s is stale; run python3 tools/levers.py --write" % OUT, file=sys.stderr)
                return 1
            print("levers: %s matches %s (%d entries)" % (OUT, DOC, len(entries)))
            return 0
        if have != want:
            with open(out_path, "w", encoding="utf-8") as fh:
                fh.write(want)
        print("levers: wrote %s (%d entries)" % (OUT, len(entries)))
        return 0

    selected = entries
    if args.confidence:
        selected = [e for e in selected if e["confidence"] == args.confidence]
    if args.section:
        selected = [e for e in selected if args.section.lower() in e["section"].lower()]
    if args.id:
        selected = [e for e in selected if e["id"] == args.id]
    if args.symptom:
        selected = search(selected, args.symptom)
        if args.limit:
            selected = selected[:args.limit]
    elif not (args.section or args.id or args.confidence):
        counts = {}
        for e in entries:
            row = counts.setdefault(e["section"], {"proven": 0, "open": 0, "uncited": 0})
            row[e["confidence"]] += 1
        for section, row in counts.items():
            print("%-48s %3d proven %2d open %2d uncited" % (section, row["proven"], row["open"], row["uncited"]))
        print("%d entries; --symptom, --section or --id to read them" % len(entries))
        return 0
    if not selected:
        print("levers: no entry matches", file=sys.stderr)
        return 1
    if args.format == "json":
        sys.stdout.write(render(selected))
    elif args.format == "prompt":
        print(format_prompt(selected))
    else:
        print("\n\n".join(format_text(e) for e in selected))
    return 0


if __name__ == "__main__":
    sys.exit(main())
