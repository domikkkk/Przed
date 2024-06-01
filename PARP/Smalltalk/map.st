Object subclass: GameMap [
    | locations connections keys staticMonsters randomMonsters lvup|

    GameMap class >> new [
        ^super new initialize.
    ]

    GameMap >> addLocation: location withDescription: description [
        locations at: location put: description.
    ]

    GameMap >> addConnectionFrom: from to: to withDirection: direction [
        connections add: (Array with: from with: direction with: to).
    ]

    GameMap >> addKey: key withLocation: location [
        keys at: location put: key.
    ]

    GameMap >> addMonster: monster withLocation: location toMonsters: monsters[
        monsters at: location put: monster.
    ]

    GameMap >> getLocationDescription: location [
        ^locations at: location ifAbsent: ['Location not found'].
    ]

    GameMap >> getConnectionsFrom: location [
    | result |
	result := connections select: [:conn | conn first = location].
	^result.
    ]

    GameMap >> getKey: location [
        ^keys at: location ifAbsent: ['Not key'].
    ]

    GameMap >> getMonster: location [
        ^staticMonsters at: location ifAbsent: [self getRandomMonster: location].
    ]

    GameMap >> getRandomMonster: location [
        | monster lv randomInt |
        monster := randomMonsters at: location ifAbsent: [^false].
        randomInt := Random new between: 1 and: 10.
        randomInt > 3 ifTrue: [^false].
        lv := #(1 1 1 1 1 2 2 3 4 5).
        randomInt := Random new between: 1 and: 10.
        monster := {monster first. (lv at: randomInt)}.
        ^monster.
    ]

    GameMap >> deleteStaticMonster: location [
        staticMonsters removeKey: location ifAbsent: [].
    ]

    GameMap >> checklvup: location [
        (lvup includes: location) ifTrue: [
            lvup := lvup copyWithout: location.
            ^true.
        ].
        ^false.
    ]

    GameMap >> initialize [
        locations := Dictionary new.
        connections := OrderedCollection new.
        keys := Dictionary new.
        staticMonsters := Dictionary new.
        randomMonsters := Dictionary new.
        lvup := #('c2' 'f2' 'a4' 'g4').

        self addKey: 'Heartwood Key' withLocation: 'a1'.
        self addKey: 'Divine Sigil Key' withLocation: 'g1'.
        self addKey: 'Stoneheart Key' withLocation: 'b5'.

        self addLocation: 'a1' withDescription: 'Forest'.
        self addLocation: 'a2' withDescription: 'Forest'.
        self addLocation: 'a3' withDescription: 'Mountains'.
        self addLocation: 'a4' withDescription: 'Mountains'.
        self addLocation: 'a5' withDescription: 'Mountains'.
        self addLocation: 'a6' withDescription: 'Valley'.
        self addLocation: 'a7' withDescription: 'Abandoned house'.

        self addLocation: 'b1' withDescription: 'Forest'.
        self addLocation: 'b2' withDescription: 'Forest'.
        self addLocation: 'b3' withDescription: 'Forest'.
        self addLocation: 'b5' withDescription: 'Cave'.
        self addLocation: 'b6' withDescription: 'Valley'.
        self addLocation: 'b7' withDescription: 'Mountains'.

        self addLocation: 'c1' withDescription: 'Forest'.
        self addLocation: 'c2' withDescription: 'Forest'.
        self addLocation: 'c3' withDescription: 'Forest'.
        self addLocation: 'c6' withDescription: 'Valley'.
        self addLocation: 'c7' withDescription: 'Valley'.

        self addLocation: 'd1' withDescription: 'Savanna'.
        self addLocation: 'd2' withDescription: 'Forest'.
        self addLocation: 'd3' withDescription: 'Forest'.
        self addLocation: 'd4' withDescription: 'Anyor Village'.
        self addLocation: 'd6' withDescription: 'Savanna'.
        self addLocation: 'd7' withDescription: 'Savanna'.

        self addLocation: 'e1' withDescription: 'Savanna'.
        self addLocation: 'e2' withDescription: 'Savanna'.
        self addLocation: 'e3' withDescription: 'Fields'.
        self addLocation: 'e4' withDescription: 'Fields'.
        self addLocation: 'e5' withDescription: 'Bridge'.
        self addLocation: 'e6' withDescription: 'Swamp'.
        self addLocation: 'e7' withDescription: 'Swamp'.

        self addLocation: 'f1' withDescription: 'Desert'.
        self addLocation: 'f2' withDescription: 'Desert'.
        self addLocation: 'f6' withDescription: 'Swamp'.
        self addLocation: 'f7' withDescription: 'Swamp'.

        self addLocation: 'g1' withDescription: 'Temple'.
        self addLocation: 'g2' withDescription: 'Desert'.
        self addLocation: 'g4' withDescription: 'Exeter Village'.
        self addLocation: 'g5' withDescription: 'Swamp'.
        self addLocation: 'g6' withDescription: 'Swamp'.
        self addLocation: 'g7' withDescription: 'Swamp'.

        self addConnectionFrom: 'a1' to: 'a2' withDirection: 'e'.
        self addConnectionFrom: 'a1' to: 'b1' withDirection: 's'.
        self addConnectionFrom: 'a2' to: 'a1' withDirection: 'w'.
        self addConnectionFrom: 'a2' to: 'a3' withDirection: 'e'.
        self addConnectionFrom: 'a2' to: 'b2' withDirection: 's'.
        self addConnectionFrom: 'a3' to: 'a2' withDirection: 'w'.
        self addConnectionFrom: 'a3' to: 'a4' withDirection: 'e'.
        self addConnectionFrom: 'a3' to: 'b3' withDirection: 's'.
        self addConnectionFrom: 'a4' to: 'a3' withDirection: 'w'.
        self addConnectionFrom: 'a5' to: 'a6' withDirection: 'e'.
        self addConnectionFrom: 'a5' to: 'b5' withDirection: 's'.
        self addConnectionFrom: 'a6' to: 'a5' withDirection: 'w'.
        self addConnectionFrom: 'a6' to: 'b6' withDirection: 's'.
        self addConnectionFrom: 'a7' to: 'a6' withDirection: 'w'.
        self addConnectionFrom: 'b1' to: 'c1' withDirection: 's'.
        self addConnectionFrom: 'b1' to: 'a1' withDirection: 'n'.
        self addConnectionFrom: 'b1' to: 'b2' withDirection: 'e'.
        self addConnectionFrom: 'b2' to: 'a2' withDirection: 'n'.
        self addConnectionFrom: 'b2' to: 'b1' withDirection: 'w'.
        self addConnectionFrom: 'b2' to: 'b3' withDirection: 'e'.
        self addConnectionFrom: 'b2' to: 'c2' withDirection: 's'.
        self addConnectionFrom: 'b3' to: 'a3' withDirection: 'n'.
        self addConnectionFrom: 'b3' to: 'b2' withDirection: 'w'.
        self addConnectionFrom: 'b3' to: 'c3' withDirection: 's'.
        self addConnectionFrom: 'b5' to: 'a5' withDirection: 'n'.
        self addConnectionFrom: 'b5' to: 'b6' withDirection: 'e'.
        self addConnectionFrom: 'b6' to: 'a6' withDirection: 'n'.
        self addConnectionFrom: 'b6' to: 'b7' withDirection: 'e'.
        self addConnectionFrom: 'b6' to: 'b5' withDirection: 'w'.
        self addConnectionFrom: 'b6' to: 'c6' withDirection: 's'.
        self addConnectionFrom: 'b7' to: 'c7' withDirection: 's'.
        self addConnectionFrom: 'b7' to: 'b6' withDirection: 'w'.
        self addConnectionFrom: 'c1' to: 'b1' withDirection: 'n'.
        self addConnectionFrom: 'c1' to: 'c2' withDirection: 'e'.
        self addConnectionFrom: 'c1' to: 'd1' withDirection: 's'.
        self addConnectionFrom: 'c2' to: 'b2' withDirection: 'n'.
        self addConnectionFrom: 'c2' to: 'c1' withDirection: 'w'.
        self addConnectionFrom: 'c2' to: 'c3' withDirection: 'e'.
        self addConnectionFrom: 'c2' to: 'd2' withDirection: 's'.
        self addConnectionFrom: 'c3' to: 'b3' withDirection: 'n'.
        self addConnectionFrom: 'c3' to: 'c2' withDirection: 'w'.
        self addConnectionFrom: 'c3' to: 'd3' withDirection: 's'.
        self addConnectionFrom: 'c6' to: 'b6' withDirection: 'n'.
        self addConnectionFrom: 'c6' to: 'c7' withDirection: 'e'.
        self addConnectionFrom: 'c6' to: 'd6' withDirection: 's'.
        self addConnectionFrom: 'c7' to: 'b7' withDirection: 'n'.
        self addConnectionFrom: 'c7' to: 'c6' withDirection: 'w'.
        self addConnectionFrom: 'c7' to: 'd7' withDirection: 's'.
        self addConnectionFrom: 'd1' to: 'c1' withDirection: 'n'.
        self addConnectionFrom: 'd1' to: 'd2' withDirection: 'e'.
        self addConnectionFrom: 'd1' to: 'e1' withDirection: 's'.
        self addConnectionFrom: 'd2' to: 'c2' withDirection: 'n'.
        self addConnectionFrom: 'd2' to: 'd1' withDirection: 'w'.
        self addConnectionFrom: 'd2' to: 'd3' withDirection: 'e'.
        self addConnectionFrom: 'd2' to: 'e2' withDirection: 's'.
        self addConnectionFrom: 'd3' to: 'c3' withDirection: 'n'.
        self addConnectionFrom: 'd3' to: 'd2' withDirection: 'w'.
        self addConnectionFrom: 'd3' to: 'd4' withDirection: 'e'.
        self addConnectionFrom: 'd3' to: 'e3' withDirection: 's'.
        self addConnectionFrom: 'd4' to: 'e4' withDirection: 's'.
        self addConnectionFrom: 'd4' to: 'd3' withDirection: 'w'.
        self addConnectionFrom: 'd6' to: 'c6' withDirection: 'n'.
        self addConnectionFrom: 'd6' to: 'e6' withDirection: 's'.
        self addConnectionFrom: 'd6' to: 'd7' withDirection: 'e'.
        self addConnectionFrom: 'd7' to: 'c7' withDirection: 'n'.
        self addConnectionFrom: 'd7' to: 'd6' withDirection: 'w'.
        self addConnectionFrom: 'd7' to: 'e7' withDirection: 's'.
        self addConnectionFrom: 'e1' to: 'd1' withDirection: 'n'.
        self addConnectionFrom: 'e1' to: 'f1' withDirection: 's'.
        self addConnectionFrom: 'e1' to: 'e2' withDirection: 'e'.
        self addConnectionFrom: 'e2' to: 'd2' withDirection: 'n'.
        self addConnectionFrom: 'e2' to: 'e1' withDirection: 'w'.
        self addConnectionFrom: 'e2' to: 'e3' withDirection: 'e'.
        self addConnectionFrom: 'e2' to: 'f2' withDirection: 's'.
        self addConnectionFrom: 'e3' to: 'd3' withDirection: 'n'.
        self addConnectionFrom: 'e3' to: 'e2' withDirection: 'w'.
        self addConnectionFrom: 'e3' to: 'e4' withDirection: 'e'.
        self addConnectionFrom: 'e4' to: 'd4' withDirection: 'n'.
        self addConnectionFrom: 'e4' to: 'e3' withDirection: 'w'.
        self addConnectionFrom: 'e4' to: 'e5' withDirection: 'e'.
        self addConnectionFrom: 'e5' to: 'e4' withDirection: 'w'.
        self addConnectionFrom: 'e5' to: 'e6' withDirection: 'e'.
        self addConnectionFrom: 'e6' to: 'd6' withDirection: 'n'.
        self addConnectionFrom: 'e6' to: 'e5' withDirection: 'w'.
        self addConnectionFrom: 'e6' to: 'f6' withDirection: 's'.
        self addConnectionFrom: 'e6' to: 'e7' withDirection: 'e'.
        self addConnectionFrom: 'e7' to: 'd7' withDirection: 'n'.
        self addConnectionFrom: 'e7' to: 'e6' withDirection: 'w'.
        self addConnectionFrom: 'e7' to: 'f7' withDirection: 's'.
        self addConnectionFrom: 'f1' to: 'e1' withDirection: 'n'.
        self addConnectionFrom: 'f1' to: 'f2' withDirection: 'e'.
        self addConnectionFrom: 'f1' to: 'g1' withDirection: 's'.
        self addConnectionFrom: 'f2' to: 'e2' withDirection: 'n'.
        self addConnectionFrom: 'f2' to: 'f1' withDirection: 'w'.
        self addConnectionFrom: 'f2' to: 'g2' withDirection: 's'.
        self addConnectionFrom: 'f6' to: 'e6' withDirection: 'n'.
        self addConnectionFrom: 'f6' to: 'g6' withDirection: 's'.
        self addConnectionFrom: 'f6' to: 'f7' withDirection: 'e'.
        self addConnectionFrom: 'f7' to: 'e7' withDirection: 'n'.
        self addConnectionFrom: 'f7' to: 'g7' withDirection: 'w'.
        self addConnectionFrom: 'f7' to: 'f6' withDirection: 's'.
        self addConnectionFrom: 'g1' to: 'f1' withDirection: 'n'.
        self addConnectionFrom: 'g1' to: 'g2' withDirection: 'e'.
        self addConnectionFrom: 'g2' to: 'f2' withDirection: 'n'.
        self addConnectionFrom: 'g2' to: 'g1' withDirection: 'w'.
        self addConnectionFrom: 'g4' to: 'g5' withDirection: 'e'.
        self addConnectionFrom: 'g5' to: 'g6' withDirection: 'e'.
        self addConnectionFrom: 'g6' to: 'f6' withDirection: 'n'.
        self addConnectionFrom: 'g6' to: 'g5' withDirection: 'w'.
        self addConnectionFrom: 'g6' to: 'g7' withDirection: 'e'.
        self addConnectionFrom: 'g7' to: 'f7' withDirection: 'n'.
        self addConnectionFrom: 'g7' to: 'g6' withDirection: 'w'.

        self addMonster: {'MiniBoss - Druid'. 2} withLocation: 'a1' toMonsters: staticMonsters.
        self addMonster: {'FINAL BOSS - Empheral Phantom'. 5} withLocation: 'a7' toMonsters: staticMonsters.
        self addMonster: {'MiniBoss - Goblin'. 4} withLocation: 'b5' toMonsters: staticMonsters.
        self addMonster: {'Elf'. 1} withLocation: 'c2' toMonsters: staticMonsters.
        self addMonster: {'Hermit'. 1} withLocation: 'f2' toMonsters: staticMonsters.
        self addMonster: {'MiniBoss - Undead Priest'. 3} withLocation: 'g1' toMonsters: staticMonsters.
        self addMonster: {'River spirit'. 0} withLocation: 'a4' toMonsters: staticMonsters.

        self addMonster: {'Wolf'. 1} withLocation: 'a2' toMonsters: randomMonsters.
        self addMonster: {'Elf'. 1} withLocation: 'a3' toMonsters: randomMonsters.
        self addMonster: {'Elf'. 1} withLocation: 'b2' toMonsters: randomMonsters.
        self addMonster: {'Wolf'. 1} withLocation: 'b3' toMonsters: randomMonsters.
        self addMonster: {'Wolf'. 1} withLocation: 'c1' toMonsters: randomMonsters.
        self addMonster: {'Elf'. 1} withLocation: 'c3' toMonsters: randomMonsters.
        self addMonster: {'Goblin'. 1} withLocation: 'c6' toMonsters: randomMonsters.
        self addMonster: {'Ocelot'. 1} withLocation: 'd1' toMonsters: randomMonsters.
        self addMonster: {'Wolf'. 1} withLocation: 'd3' toMonsters: randomMonsters.
        self addMonster: {'Ocelot'. 1} withLocation: 'd6' toMonsters: randomMonsters.
        self addMonster: {'Ocelot'. 1} withLocation: 'd7' toMonsters: randomMonsters.
        self addMonster: {'Lion'. 1} withLocation: 'e2' toMonsters: randomMonsters.
        self addMonster: {'Goblin'. 1} withLocation: 'e4' toMonsters: randomMonsters.
        self addMonster: {'Drowned'. 1} withLocation: 'e6' toMonsters: randomMonsters.
        self addMonster: {'Hermit'. 1} withLocation: 'f1' toMonsters: randomMonsters.
        self addMonster: {'Drowned'. 1} withLocation: 'f6' toMonsters: randomMonsters.
        self addMonster: {'Drowned'. 1} withLocation: 'f7' toMonsters: randomMonsters.
        self addMonster: {'Naiad'. 1} withLocation: 'g5' toMonsters: randomMonsters.
        self addMonster: {'Drowned'. 1} withLocation: 'g7' toMonsters: randomMonsters.
    ]
]
