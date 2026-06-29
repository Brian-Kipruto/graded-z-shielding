# Handoff — YYYY-MM-DD — Session N (<title>) complete, next: Session N+1 (<title>)

Project: **Graded-Z Shielding MSc** — University of Nairobi, Institute of Nuclear Science & Technology
Author: Brian Kipruto Kosgei (FNS6/48630/2025)
Last completed: **Session N — <title>** (commit `<sha>` on `<branch>`, pushed to GitHub)
Current branch: `<branch>` (state: <clean / has-uncommitted / pushed-not-merged>)
Next session: **Session N+1 — <title>**

---

## Repo state — read first

<short paragraph: where the repo is, branch state, anything Brian needs to resolve before writing code>

**Before writing any code at session start, ask Brian to paste:**

```bash
cd ~/projects/graded-z-shielding
git status
git log --oneline | head -5
geant4-config --version
ls include/ src/
```

---

## Why Session N+1 next

<one paragraph: what this session unlocks. Be specific about why NOT doing it would block later sessions.>

---

## Scope of Session N+1

- <bullet list of files to create>
- <bullet list of files to modify>
- <verification step>
- <commit + push>

Estimated time: <N> minutes.

---

## Carry-forward technical notes (landmines)

<the list of bugs-not-yet-made. Old entries carry forward; new entries added at the end of each session as gotchas are discovered.>

---

## Brian's learning state — assume known

<list of C++/Geant4 concepts already covered in working code. Add to this list at the end of each session.>

---

## Brian's learning state — still being introduced

<list of concepts coming up. Remove from here and add to the "assume known" list as each is covered.>

---

## Open decisions (mid-flight)

<things deferred with reasoning. Remove when decided; add an ADR if it's a real architectural choice.>

---

## Workflow rules (Graded-Z thesis edition, non-negotiable)

1. Concept first, code second.
2. Small focused chunks, one concept per file when possible, heavy comments.
3. No big silent code dumps — 20–80 line chunks with brief explanations.
4. Paste-output verification at each step.
5. End each session with: working build, git commit, push, retrospective.
6. ADR for every non-trivial decision.
7. Don't reintroduce known bugs (see Carry-forward).
8. Paste errors verbatim.
9. Forward declarations in headers, full includes in .cc files.
10. `override` on every virtual override.
11. `true` for overlap checking in `G4PVPlacement` during dev.

---

## Vault notes to skim before starting

<bullet list of specific Obsidian vault notes relevant to the upcoming session>

---

## Path reminders

- C++ source/headers/macros: relative to `~/projects/graded-z-shielding/`.
- Build dir: `~/projects/graded-z-shielding/build/`.
- Binary: `~/projects/graded-z-shielding/build/graded-z`.
- Geant4 install: `/home/brian/geant4/geant4-v11.2.1-install/` (auto-sourced).

---

## Fresh-terminal start sequence

```bash
cd ~/projects/graded-z-shielding
geant4-config --version
cd build && make -j$(nproc)
./graded-z
```

(Use `cmake .. && make -j$(nproc)` if new files were added since last build.)

---

## Files to have in context for Session N+1

Required:
- <files>

Reference (read if needed):
- <files>

---

## Retrospective notes (Session N, written YYYY-MM-DD)

What worked:
- <bullets>

What to do differently next time:
- <bullets>

What surprised:
- <bullets>

---

*Next handoff to be written at end of Session N+1.*
