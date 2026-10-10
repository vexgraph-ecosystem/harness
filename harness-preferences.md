# harness — Repo-Local Living Preferences
> Repo-local preferences governed by the Living Documentation Law.
> Universal Supreme Constitution: workspace-root preferences.md, published on Gist.

## 0. Constitution Link (supreme)
- [preferences.md](https://gist.github.com/vex-graph/4132a6c45cb6d3797c3e8eff2e94035a) — real, Git-ignored workspace-root file at ../../../preferences.md, not a tracked Vexspoke file or symlink.
- All universal laws in `../../../preferences.md` are mandatory and binding across the ecosystem.
- This document codifies **exclusive** preferences for `harness` (R4 agent interface). harness is the user's **own agent**, integrated with this ecosystem. R4 borrows Relational Engine memory/IO and Vexspoke CPU/behavior; it consumes `api-haven` connectors **as-is** and composes `darling-framework` for interface. This blueprint has no implemented engine integration; connector/GPU/OS implementation ownership does not move.

## 1. Repo-Local Law Index (Binding Matrix)

Universal laws are inherited from the canonical `../../../preferences.md` Index; this table indexes the additional laws specific to this repository.

| Law Title | Scope | Enforcement |
| :--- | :--- | :--- |
| **Harness Host Boundary Law** | R4 agent interface | Mandatory for `harness` |
| **Agent Integration Law** | R4 agent execution | Mandatory for `harness` |

## 2. Exclusive Repo-Local Laws (FULL PROSE RESTATEMENT)

### Harness Host Boundary Law

#### Definition:
`harness` is the user's **own agent**, an R4 interface that integrates this
ecosystem rather than a third-party agent host. It borrows Relational Engine
memory/IO and Vexspoke CPU/behavior, consumes `api-haven`'s connectors and
`harness_run`/`harness_poll` seams **as-is** (opaque handles + fn-tables, the
Conflict Triage Law canonical move), composes `darling-framework` for interface,
and drives R5 applications through registered seams. It owns no connector,
transport, session, GPU or OS implementation of its own.

#### The Why:
The R4 tier is interfaces, not drivers. If harness re-implemented an api-haven
connector or a Graphvex pipeline, the ecosystem would grow a second, divergent
owner of the same contract — the exact drift the Vertical Integration Law
forbids. Consuming api-haven as-is keeps one owner per seam and lets the agent
focus purely on operating the user's own things.

#### The Rule:
1. **Interface tier, own agent.** harness borrows `relational-engine`,
   `vexspoke`, `api-haven` and `darling-framework` public contracts; it never
   includes R5 engine or supervisor headers, and is never included by R1/R2/R3.
2. **api-haven as-is.** Connector and `harness_run`/`harness_poll` shapes are
   consumed unchanged; harness supplies the injected driver behind those seams,
   never a parallel connector implementation.
3. **R5 through seams.** R5 applications are driven through registered opaque
   handles + fn-tables, never by `#include`ing an R5 header.
4. **Tools, not includes.** `func` and `b` are personal tools invoked as bounded
   child processes (the Bounded Wait Law); they are never `#include`d.

---

### Agent Integration Law

#### Definition:
The agent operates the user's **own** things — projects, external tools and R5
applications — through the ecosystem's registered contracts. Orchestration is
expressed as `func`'s **compile-time opcodes** and compiled native artifacts,
never a shipped interpreted runtime; every external action is a bounded child.

#### The Why:
An agent that reaches into R5 internals, or ships an interpreted orchestration
engine, couples itself to unstable surfaces and drags a runtime into every host.
Integrating only through registered seams keeps the agent honest to the Vertical
Integration Law; compile-time opcode orchestration keeps it deterministic,
dependency-free and legible to the AI pair system.

#### The Rule:
1. **Integrate only via contracts.** Projects, tools and R5 apps are reached
   through declared seams (opaque handle + fn-table); no reaching into another
   tier's internals. This is a harness agent scoped to this ecosystem, not a
   general-purpose host.
2. **Compile-time, not interpreted.** Orchestrations compile to native code
   through `func`; no interpreted orchestration engine ships as runtime state.
3. **Bounded children only.** Every external tool is a bounded child (100 ms reap
   slices, `SIGTERM` cancel — the Bounded Wait Law); no unbounded wait, no
   `system()`.
4. **Cold validation.** Agent input is validated once at the cold seam (the
   Cold-Strict, Hot-Minimal Validation Law); failures reject loudly (the THROW Law).
5. **Agent objects, not duplicate drivers.** Planned Model, Prompt, Conversation,
   Answer, Question, Tool, ToolRegistry and Harness objects own agent policy,
   history and interface state. HarnessMcp describes the agent's own tool/resource
   surface; protocol parsing/hosting and external MCP transport consume API Haven
   contracts, never a parallel R4 implementation. The vocabulary is planned, not
   an implemented API or model/provider integration claim.
6. **Proof before trust.** Future mirrored `tests/harness/` owners must prove
   registry growth/exhaustion, bounded retained history/output, failure/recovery,
   cancellation and actual tool/provider seams. Legal shared-state pressure follows
   the Deliberate Exhaustion and Backend Trust Law; fake providers or documentation
   checks alone establish neither live integration nor production readiness.

---

## 3. Repo-Local Extensions (managed, per the Conflict Triage Law)

### Current draft and IDE evidence boundary

`src/space/` now contains unfinished ModelUser, Channel, Message and Task class
pairs and header-only support. They are not live agent/provider/UI integration.
Their lifecycle/identity/accessor contracts and message projections still require
review and behavioral owners; this metadata cycle does not approve those gaps.

The workspace owns all editor indexing and supplies the local Vexspoke headers.
It discovers `.c` and `.h` sources recursively; this repository owns no CMake
entry. Workspace compiler tests prove source contexts, header resolution and
recursive discovery only,
not actual highlighting/inlay appearance or runtime dependency closure. Existing
planned agent objects and ownership boundaries above are unchanged.

;;INTENTION("R4 agent interface: the user's own agent integrated with the ecosystem; consumes api-haven as-is; drives projects/tools/R5 apps through registered seams; owns no connector/GPU/OS implementation; bounded child tools only.")

## 4. Readiness Cross-Reference (Living Documentation Law)

- Feature readiness matrix: [harness](https://gist.github.com/vex-graph/6943f92acb931b25dad1073c46da6ce7#file-harness-md).
- Open blockers and deferred decisions: [ecosystem blockers Gist](https://gist.github.com/vex-graph/e921fa188eebbd0c68c4e59646109887).
