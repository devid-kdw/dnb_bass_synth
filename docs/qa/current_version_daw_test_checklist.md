# Trenutna Verzija - DAW Test Checklist i Ocekivanja

Datum: 2026-02-22  
Scope: build nakon P7 post-gate DAW hotfix paketa (prije P8)

## 1. Sto je aktivno u ovoj verziji

Aktivni host/UI parametri (APVTS):
- `style.mode` (Tech / Neuro / Dark)
- `env.amp.att`
- `env.amp.rel`
- `macro.neuro_formant`
- `macro.fm_metal`
- `macro.roller_dynamics`
- `macro.liquid_depth`
- `macro.style_morph`
- `macro.sub_punch`
- `macro.fm_pressure`
- `macro.cutoff_motion`
- `macro.fold_bite`
- `macro.table_drift`
- `macro.smash_glue`

Frontend kontrole:
- Style selector: `Tech`, `Neuro`, `Dark`
- 10 macro rotary kontrola (4 primary + 6 advanced)
- 1 style morph slider
- stilizirani vizualni panel (reaktivan na output level)

## 2. Brzi Smoke Test (obavezno)

1. Plugin scan i load
- Koraci:
  - Rescan VST3 u DAW-u.
  - Ucitaj `DnB Bass Synth` na instrument track.
- Ocekivano:
  - Plugin se ucita bez crasha.
  - GUI se otvara (style selector + style morph + 10 macro kontrola).

2. MIDI i audio izlaz
- Koraci:
  - Posalji MIDI note (npr. C1-C3), kratke i duge note.
- Ocekivano:
  - Stabilan output bez dropova.
  - Nema click/glitch artefakata u normalnom radu.

## 3. Kontrole koje moraju raditi

1. `style.mode`
- Test:
  - Prebacuj `Tech -> Neuro -> Dark` uz isti pattern.
- Ocekivano:
  - Cuje se razlika karaktera.
  - `Dark` je agresivniji, `Tech` kontroliraniji.

2. `macro.neuro_formant`
- Test:
  - Sweep 0 -> 1.
- Ocekivano:
  - Primjetna promjena tonalnog karaktera/boje.

3. `macro.fm_metal`
- Test:
  - Sweep 0 -> 1 u sva 3 stila.
- Ocekivano:
  - U sva 3 stila mora biti cujan efekt (nije no-op).
  - Intenzitet je style-bounded: `Tech < Neuro < Dark`.

4. `macro.roller_dynamics`
- Test:
  - Sweep 0 -> 1 na istom note loopu.
- Ocekivano:
  - Cuje se promjena dinamike/movementa.

5. `macro.liquid_depth`
- Test:
  - Sweep 0 -> 1.
- Ocekivano:
  - Zvuk postaje mekse/tamnije boje.

6. `macro.style_morph`
- Test:
  - Sweep 0 -> 1 i automation lane.
- Ocekivano:
  - Cuje se kontinuirana promjena karaktera.

7. Dodatnih 6 makroa
- Test:
  - `sub_punch`, `fm_pressure`, `cutoff_motion`, `fold_bite`, `table_drift`, `smash_glue` sweep 0 -> 1.
- Ocekivano:
  - Svaki parametar mora imati cujan utjecaj (nije dead/no-op).

8. `env.amp.att` i `env.amp.rel`
- Test:
  - Automacija ili host kontrola min/max.
- Ocekivano:
  - Kraci attack = brzi onset.
  - Dugi release = duzi rep.

## 4. UI Vizualni Test

1. Knob endpoint
- Test:
  - Postavi bilo koji knob na tocno `0%` i `100%`.
- Ocekivano:
  - Value arc/glow odgovara tocnim endpointovima (bez vizualnog "kratkog" luka na 100%).

2. Center visual panel
- Test:
  - Sviraj note razlicitih dinamika i gledaj sredisnji panel.
- Ocekivano:
  - Panel je reaktivan (bar + wave animacija).
  - Nema preklapanja starih statickih wave/spectrum layera preko runtime animacije.

Napomena:
- Ovo je stilizirani feedback panel, nije referentni FFT analyzer.

## 5. Host Automation Test

1. Napravi automation lane za sve aktivne parametre.
2. Playback 16-32 bar.

Ocekivano:
- Parametri odgovaraju na automation bez pucanja audio-a.
- Nema mrtvih aktivnih parametara.

## 6. Sto NE treba ocekivati u ovoj verziji

1. Full release CI/CD workflow jos nije zatvoren (to je P8 scope).
2. Vizualni panel nije metroloski analyzer (samo performansni/stilizirani feedback).

## 7. Fail kriteriji (odmah prijaviti)

- Plugin se ne ucitava ili rusi DAW.
- Nema audio izlaza na validan MIDI input.
- Bilo koja aktivna kontrola je no-op.
- Knob value arc ne doseze tocni endpoint na `100%`.
- Center panel prikazuje staticne overlaye koji vizualno kolidiraju s runtime animacijom.
- Automation uzrokuje dropout/freeze/hard artefakte.

## 8. Preporuceni format biljeski za test

- DAW + verzija:
- OS:
- Buffer/SR:
- Test case:
- Rezultat (`PASS`/`FAIL`):
- Kratka napomena + eventualni screenshot/audio clip:
