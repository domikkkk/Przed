:- dynamic i_am_at/1.
:- dynamic monster/3.
:- dynamic boss_monster/3.
:- dynamic equipment/1.
:- dynamic player_weapon_level/1.
:- dynamic can_upgrade/1.
:- dynamic chat/2.
:- retractall(i_am_at(_)).
:- retractall(equipment(_)).
:- consult(map).
% :- consult(display_map).

respawn :-
    i_am_at(Here),
    retract(i_am_at(Here)),
    assert(i_am_at(d4)),
    write('You will need stronger weapon to defeat that monster!'), nl,
    write('Local medic has found your body and brang to Anyor!'), nl,
    look.

try_lvl5 :-
    player_weapon_level(Level),
    (
        Level = 5 ->
        retractall(chat(quest, _)),
        write('NEW QUEST ADDED: Kill Empheral Phantom.'), nl,
        assert(chat(quest, 'Kill Empheral Phantom.'))
        ;
        true
    ).

try_unlock_Exeter :-
    assert(path(g5, w, g4)),  % Add possibility to entry to Exeter
    nl, write("Unlocked Exeter"), nl.

talking_to_jake_next_exeter :-
    chat(quest, Desc),
    (
        Desc = 'Talk to Jake in Anyor.' ->
        retractall(chat(quest, _)),
        try_unlock_Exeter,
        write('NEW QUEST ADDED: Find Exeter to get a better weapon.'), nl,
        assert(chat(quest, 'Find Exeter to get a better weapon.'))
        ;true    
    ).

try_unlock_Final_Boss :-
    (
        has_all_keys ->
        assert(path(a6, e, a7)),
        nl, write("Unlocked Final Boss"), nl,
        retractall(chat(quest, _)),
        write('NEW QUEST ADDED: Talk to Jake in Anyor.'), nl,
        assert(chat(quest, 'Talk to Jake in Anyor.')),
        retractall(chat(jake, _)),
        assert(chat(jake, 'So it is true. You need to prepare. Find Exeter to get a better weapon.'))
        ;true
    ).


upgrade :-
    i_am_at(Loc),
    (
        can_upgrade(Value) ->
        retract(player_weapon_level(PlayerWeaponLevel)),
        NewLevel is PlayerWeaponLevel + 1,
        retract(lvlup(Loc)),
        assert(player_weapon_level(NewLevel)),
        nl, write('WEAPON UPGRADE FOUND!!!'), nl,
        write('Your weapon has been upgraded to level '), write(NewLevel), nl,
        try_lvl5,
        retract(can_upgrade(Value))
        ;
        true
    ).


take_key :-
    i_am_at(Loc),
    (   
        key(Loc, Key) -> 
        nl, write('You have found a '), write(Key), nl,
        assert(equipment(Key)),
        write('You have taken the '), write(Key), nl,
        try_unlock_Final_Boss;
        true
    ).
boss_combat(Monster) :-
    write('You are battling '), write(Monster), nl,
    player_weapon_level(PlayerWeaponLevel),
    i_am_at(Loc),
    boss_monster(Loc, Monster, MonsterLevel),
    (
        PlayerWeaponLevel >= MonsterLevel ->
        write('You have defeated the '), write(Monster), write(' with your weapon level '), write(PlayerWeaponLevel), write('!'), nl,
        retract(boss_monster(Loc, Monster, MonsterLevel)),
        retractall(chat(quest, _)),
        write('YOU FINISHED A GAME. CONGRATULATIONS!'), nl, nl, nl,
        halt
        ;
        write('You were defeated by the '), write(Monster), nl,
        respawn
    ).

combat(Monster) :-
    write('You are battling '), write(Monster), nl,
    player_weapon_level(PlayerWeaponLevel),
    i_am_at(Loc),
    monster(Loc, Monster, MonsterLevel),
    (
        PlayerWeaponLevel >= MonsterLevel ->
        write('You have defeated the '), write(Monster), write(' with your weapon level '), write(PlayerWeaponLevel), write('!'), nl,
        retract(monster(Loc, Monster, MonsterLevel)),
        retractall(can_upgrade(_)),
        assert(can_upgrade(yes)),
        take_key;
        write('You were defeated by the '), write(Monster), nl,
        respawn
    ).
list_characters_at(Place) :-
    findall(Character, char(Place, Character), Characters),
    (
        Characters \= [] ->
        write('Characters present: '), nl,
        write_characters(Characters)
        ; true
    ).

write_characters([]).
write_characters([Character|Rest]) :-
    write(Character), nl,
    write_characters(Rest).

/* This rule just writes out game instructions. */
look :-
    i_am_at(Place),
    write('You are in '), describe(Place),
    write('You are at '), write(Place), nl,
    (   
        monster(Place, Monster, Level) ->
        write('A wild '), write(Monster), write(' [lvl '), write(Level), write('] appears!'), nl,
        combat(Monster)
        ;true
    ),
    (   
        boss_monster(Place, Monster, Level) ->
        write('BOSS APPEARED: '), write(Monster), write(' [lvl '), write(Level), write(']'), nl,
        boss_combat(Monster)
        ;true
    ),
    (
        lvlup(Place) ->
        upgrade;
        true
    ),
    list_characters_at(Place),
    nl.

n :- go(n).

s :- go(s).

e :- go(e).

w :- go(w).


bag :- 
    write('Your equipment: '), nl,
    findall(Item, equipment(Item), Equipment_list),
    write_equipment(Equipment_list), nl.

write_equipment([]).
write_equipment([Item|Rest]) :-  % bierze pierwszy item który znajdzie i wypisuje
    write('- '), write(Item), nl,
    write_equipment(Rest).  % rekurencyjnie wypisuje dla reszty itemów


has_all_keys :-
    findall(Key, equipment(Key), Keys),
    length(Keys, Number_of_keys),
    Number_of_keys = 3.
    


/* This rule tells how to move in a given direction. */

go(Direction) :-
        i_am_at(Here),
        path(Here, Direction, There),
        retract(i_am_at(Here)),
        assert(i_am_at(There)),
        (
            There = g4 ->
            retractall(can_upgrade(_)),
            assert(can_upgrade(yes));
            true
        ),
        !, look.

go(_) :-
        write('You can\'t go that way.'), nl.


look(Direction) :-
        i_am_at(Here),
        path(Here, Direction, There),
        write('You are looking at '), describe(There), nl,
        !.

look(_) :-
        write('You can\'t go that way.'), nl.

quest :-
    write("CURRENT QUEST: "),
    chat(quest, Desc),
    write(Desc).

talk(Person) :-
    i_am_at(Loc),
    char(Loc, EPerson) ->
        (
            EPerson = Person ->
            (   EPerson = 'jake' ->
                    chat(EPerson, Desc),
                    talking_to_jake_next_exeter,
                    write(Desc), nl
                ;
                    chat(EPerson, Desc),
                    write(Desc), nl
            )
            ;
            write("Cannot talk to him!"), nl
        )
    ;
    write("Cannot talk to him!"), nl.

instructions :-
    nl,
    write('Enter commands using standard Prolog syntax.'), nl,
    write('Available commands are:'), nl,
    write('start.             -- to start the game.'), nl,
    write('n.  s.  e.  w.     -- to go in that direction.'), nl,
    write('look.              -- to look around you again.'), nl,
    write('look(Direction).   -- to look in one of four directions'), nl,
    write('instructions.      -- to see this message again.'), nl,
    write('bag.               -- to see your equipment'), nl,
    write('talk(Person).      -- to talk to Person'), nl,
    write('quest.             -- to see your quests'), nl,
    write('halt.              -- to end the game and quit.'), nl,
    nl.


/* This rule prints out instructions and tells where you are. */

start :-
    assert(i_am_at(d4)),
    assert(player_weapon_level(1)),
    write('In a realm veiled by ancient lore, three guardians protected fragments of a mysterious key.'), nl,
    write('Druid guarded the forest, the Undead Priest watched over the temple, and a formidable Goblin held the key fragment in treacherous caves.'), nl,
    write('Legends whispered of an elusive entity, the Ephemeral Phantom, residing in the abandoned house, said to hold the power to shape the realm\'s destiny.'), nl, 
    write('Only a brave soul could confront this being and determine the realm\'s fate.'), nl,
    assert(chat(jake, 'Is it only a legend? Perhaps...')),
    instructions,
    assert(chat(quest, 'Collect 3 key fragments.')),
    look,
    write('NEW QUEST ADDED: Collect 3 key fragments.'), nl.