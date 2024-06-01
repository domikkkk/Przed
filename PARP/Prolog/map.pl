:- discontiguous describe/1.
:- discontiguous path/3.
:- discontiguous monster/3.
:- dynamic path/3.
:- dynamic lvlup/1.
% ==============================
% ROW A
% A1 - Forest [key] [MiniBoss Druid lvl2]


describe(a1) :- forest.
path(a1, e, a2).
path(a1, s, b1).

% A2 - Forest


describe(a2) :- forest.

path(a2, w, a1).
path(a2, e, a3).
path(a2, s, b2).

% A3 - Mountains


describe(a3) :- mountain.

path(a3, w, a2).
path(a3, e, a4).
path(a3, s, b3).

% A4 - River source [weapon lvl up]


describe(a4) :- river_src.

path(a4, w, a3).

% A5 - Mountains


describe(a5) :- mountain.

path(a5, e, a6).
path(a5, s, b5).

% A6 - Valley


describe(a6) :- valley.

path(a6, w, a5).
% path(a6, e, a7). - currently locked
path(a6, s, b6).

% A7 - Abandoned house [Final Boss - Bad Spirit lvl5]


describe(a7) :- abandoned_house.

path(a7, w, a6).

% ==============================
% ROW B
% B1 - Forest


describe(b1) :- forest.

path(b1, s, c1).
path(b1, n, a1).
path(b1, e, b2).

% B2 - Forest [Elf lvl1]


describe(b2) :- forest.

path(b2, s, c2).
path(b2, n, a2).
path(b2, e, b3).
path(b2, w, b1).

% B3 - Forest [Wolf lvl1]


describe(b3) :- forest.

path(b3, s, c3).
path(b3, n, a3).
path(b3, w, b2).

% B4 - River



% B5 - Cave [key] [MiniBoss - Goblin lvl4]

describe(b5) :- cave.

path(b5, n, a5).
path(b5, e, b6).

% B6 - Valley [Goblin lvl1]


describe(b6) :- valley.

path(b6, s, c6).
path(b6, n, a6).
path(b6, e, b7).
path(b6, w, b5).

% B7 - Mountains

describe(b7) :- mountain.

path(b7, s, c7).
path(b7, w, b6).

% ==============================
% ROW C
% C1 - Forest


describe(c1) :- forest.

path(c1, s, d1).
path(c1, n, b1).
path(c1, e, c2).

% C2 - Forest [Elf lvl1] [weapon lvl up]


describe(c2) :- forest.

path(c2, s, d2).
path(c2, n, b2).
path(c2, e, c3).
path(c2, w, c1).

% C3 - Forest


describe(c3) :- forest.

path(c3, s, d3).
path(c3, n, b3).
path(c3, w, c2).

% C4 - River



% C5 - River



% C6 - Valley [Goblin lvl1]


describe(c6) :- valley.

path(c6, s, d6).
path(c6, n, b6).
path(c6, e, c7).

% C7 - Valley

describe(c7) :- valley.

path(c7, s, d7).
path(c7, n, b7).
path(c7, w, c6).

% ==============================
% ROW D
% D1 - Savanna


describe(d1) :- savanna.

path(d1, s, e1).
path(d1, n, c1).
path(d1, e, d2).

% D2 - Forest


describe(d2) :- forest.

path(d2, s, e2).
path(d2, n, c2).
path(d2, e, d3).
path(d2, w, d1).

% D3 - Forest


describe(d3) :- forest.

path(d3, s, e3).
path(d3, n, c3).
path(d3, w, d2).
path(d3, e, d4).

% D4 - Aynor Village [spawn]


describe(d4) :- anyor.

path(d4, s, e4).
path(d4, w, d3).


% D5 - River



% D6 - Savanna


describe(d6) :- savanna.

path(d6, s, e6).
path(d6, n, c6).
path(d6, e, d7).

% D7 - Savanna

describe(d7) :- savanna.

path(d7, s, e7).
path(d7, n, c7).
path(d7, w, d6).

% ==============================
% ROW E
% E1 - Savanna


describe(e1) :- savanna.

path(e1, s, f1).
path(e1, n, d1).
path(e1, e, e2).

% E2 - Savanna [Lion lvl1]


describe(e2) :- savanna.

path(e2, s, f2).
path(e2, n, d2).
path(e2, e, e3).
path(e2, w, e1).

% E3 - Fields


describe(e3) :- fields.

path(e3, n, d3).
path(e3, w, e2).
path(e3, e, e4).

% E4 - Fields


describe(e4) :- fields.

path(e4, n, d4).
path(e4, w, e3).
path(e4, e, e5).

% E5 - Bridge


describe(e5) :- bridge.

path(e5, w, e4).
path(e5, e, e6).

% E6 - Swamp [Drowned lvl1]


describe(e6) :- swamp.

path(e6, s, f6).
path(e6, n, d6).
path(e6, e, e7).
path(e6, w, e5).

% E7 - Swamp

describe(e7) :- swamp.

path(e7, s, f7).
path(e7, n, d7).
path(e7, w, e6).

% ==============================
% ROW F
% F1 - Desert


describe(f1) :- desert.

path(f1, s, g1).
path(f1, n, e1).
path(f1, e, f2).

% F2 - Desert [Hermit lvl1] [weapon lvl up]


describe(f2) :- desert.

path(f2, s, g2).
path(f2, n, e2).
path(f2, w, f1).

% F3 - River



% F4 - River



% F5 - River



% F6 - Swamp


describe(f6) :- swamp.

path(f6, s, g6).
path(f6, n, e6).
path(f6, e, f7).

% F7 - Swamp

describe(f7) :- swamp.

path(f7, s, g7).
path(f7, n, e7).
path(f7, w, f6).

% ==============================
% ROW G
% G1 - Temple [key] [Undead Priest lvl3]


describe(g1) :- temple.

path(g1, n, f1).
path(g1, e, g2).

% G2 - Desert


describe(g2) :- desert.

path(g2, n, f2).
path(g2, w, g1).

% G3 - River



% G4 - Exeter Village [medic] [weaponsmith with lvl5 weapon]


describe(g4) :- exeter.

path(g4, e, g5).

% G5 - Swamp [Naiad lvl1]


describe(g5) :- swamp.

% path(g5, w, g4).  % Locked
path(g5, e, g6).

% G6 - Swamp


describe(g6) :- swamp.

path(g6, n, f6).
path(g6, w, g5).
path(g6, e, g7).

% G7 - Swamp [Drowned lvl10]


describe(g7) :- swamp.

path(g7, n, f7).
path(g7, w, g6).

% Fields descriptions
forest :- write('forest.'), nl.
mountain :- write('mountains.'), nl.
river_src :- write('source.'), nl.
valley :- write('valley.'), nl.
abandoned_house :- write('abandoned house.'), nl.
cave :- write('cave.'), nl.
savanna :- write('savanna.'), nl.
swamp :- write('swamp.'), nl.
desert :- write('desert.'), nl.
anyor :- write('Anyor.'), nl.
fields :- write('fields.'), nl.
temple :- write('temple.'), nl.
bridge :- write('bridge.'), nl.
exeter :- write('Exeter.'), nl.


% Monsters
monster(a1, 'MiniBoss - Druid', 2).
boss_monster(a7, 'FINAL BOSS - Ephemeral Phantom', 5).
monster(b2, 'Elf', 1).
monster(b3, 'Wolf', 1).
monster(b5, 'MiniBoss - Goblin', 4).
monster(b6, 'Goblin', 1).
monster(c2, 'Elf', 1).
monster(c6, 'Goblin', 1).
monster(e2, 'Lion', 1).
monster(e6, 'Drowned', 1).
monster(f2, 'Hermit', 1).
monster(g1, 'MiniBoss - Undead Priest', 3).
monster(g5, 'Naiad', 1).
monster(g7, 'Drowned', 10).
monster(a4, 'River spirit', 0).
lvlup(c2).
lvlup(f2).
lvlup(a4).
lvlup(g4).

%keys
key(a1, 'Heartwood Key').
key(g1, 'Divine Sigil Key').
key(b5, 'Stoneheart Key').

char(d4, 'jake').
