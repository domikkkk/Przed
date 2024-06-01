"The germ of a text adventure game
Marcin Szlenk 2022"

"Game class

Responsibilities:
* print/read outputs/inputs
* handle game loop
* handle 'instructions' and 'halt' commands

Collaborators:
* ..."

Object subclass: Game [
    | currentQuest isGameOver currentLocation worldMap eq weaponLv |

    introductionText := #(
        'In a realm veiled by ancient lore, three guardians protected fragments of a mysterious key.'
        'Druid guarded the forest, the Undead Priest watched over the temple, and a formidable Goblin held the key fragment in treacherous caves.'
        'Legends whispered of an elusive entity, the Ephemeral Phantom, residing in the abandoned house, said to hold the power to shape the realm''s destiny.'
        'Only a brave soul could confront this being and determine the realm''s fate.'
        ''
    ).

    instructionsText := #(
        'Available commands are:'
        ''
        'instructions  -- to see these instructions.'
        'quit          -- to end the game and quit.'
        'bag           -- to see your equipment.'
        'w	       -- go west.'
        'n	       -- go north.'
        'e	       -- go east.'
        's	       -- go south.'
        'quest	       -- print current quest'
    ).
 
    Game class >> new [
        | g |
        g := super new.
        g init.
        ^g
    ]

    Game >> changeQuest: newQuest [
	| desc |
	desc := 'QUEST FINISHED: ', currentQuest.
	self printLines: (Array with: desc).
	desc := 'NEW QUEST ADDED: ', newQuest.
	self printLines: (Array with: desc).
	currentQuest := newQuest.
    ]
    
    Game >> printQuest [
	| desc |
	desc := 'CURRENT QUEST: ', currentQuest.
	self printLines: (Array with: desc).
    ] 

    Game >> init [
        isGameOver := false.
	    currentLocation := 'd4'.
	    worldMap := GameMap new.
        eq := OrderedCollection new.
        weaponLv := 1.
	    currentQuest := 'Collect 3 key fragments.'.
    ]

    Game >> look [
	| description monster lvUp|
        monster := worldMap getMonster: currentLocation.
        description := 'You are in ', (worldMap getLocationDescription: currentLocation), ' (', currentLocation,  ')'.
        self printLines: (Array with: description).
        description := 'Your level: ', (weaponLv printString).
        self printLines: (Array with: description).
        monster = false ifFalse: [
            description := 'A wild ', (monster first), ' [lv ', (monster second printString), '] appears!!!'.
            self printLines: (Array with: description).
            self combat: monster on: currentLocation.
        ].
        lvUp := worldMap checklvup: currentLocation.
        lvUp ifTrue: [
            weaponLv := weaponLv + 1.
            description := 'Weapon upgrade has been found. Your level: ', weaponLv printString.
            self printLines: (Array with: description).
            weaponLv = 4 ifTrue: [
                worldMap addConnectionFrom: 'g5' to: 'g4' withDirection: 'w'.                
            ].
	    weaponLv = 5 ifTrue: [
		self changeQuest: 'Kill Empheral Phantom.'.
	    ].
        ].
    ]

    Game >> dead [
        | description |
        description := #(
            'You have been slain'
            'Local medic has found your body...'
            ''
        ).
        self printLines: description.
        currentLocation := 'd4'.
        ^ self look.
    ]

    Game >> combat: monster on: location [
        | monsterlv description key|
        monsterlv := monster second.
        description := 'You are fighting with ', monster first.
        self printLines: (Array with: description).
        monsterlv > weaponLv ifTrue: [
            ^ self dead.
        ].
        worldMap deleteStaticMonster: location.
        description := 'You have slain ', monster first.
        self printLines: (Array with: description).
        monster first = 'FINAL BOSS - Empheral Phantom' ifTrue: [
            description := 'YOU FINISHED THE GAME. CONGRATULATIONS!'.
            self printLines: (Array with: description).
            isGameOver := true.
        ].
        key := self addKey: location.
        key = 'Not key' ifFalse: [
            description := #(
                'Key was found. Check your bag.'
                ''
            ).
            self printLines: description.
            eq size = 3 ifTrue: [
                worldMap addConnectionFrom: 'a6' to: 'a7' withDirection: 'e'.
		        self changeQuest: 'Find Exeter to get a better weapon.'.
            ].
        ].
    ]

    Game >> addKey: location [
        | key |
        key := worldMap getKey: location.
        key = 'Not key' ifFalse: [
            eq add: key.
        ].
        ^key.
    ]

    "Print strings from array in separate lines."
    Game >> printLines: anArray [
        anArray do: [ :string | Transcript show: string; cr ]
    ]

    Game >> printIntroduction [
       self printLines: introductionText.
    ]

    Game >> printInstructions [
        self printLines: instructionsText.
    ]

    Game >> readCommand [
        Transcript show: '> '.
        ^ FileStream stdin nextLine
    ]
    Game >> move: direction [
	| filteredConnections chosenConnection |
	filteredConnections := worldMap getConnectionsFrom: currentLocation.
	chosenConnection := (filteredConnections select: [:conn | conn second = direction]).

        chosenConnection isEmpty
            ifTrue: [
                Transcript show: 'You cannot go there!'; nl.
            ]
            ifFalse: [
                currentLocation := chosenConnection first third.
                self look.
            ].
    ]

    "Run the game."
    Game >> run [
        | cmd isUnknown newQuest |

        self printIntroduction.
        self printInstructions.
	    self look.
	    self printQuest.
        "Game loop."
        [isGameOver] whileFalse: [
        isUnknown := true.
        cmd := self readCommand.

        cmd = 'instructions' ifTrue: [
            self printInstructions.
            isUnknown := false
        ].

        cmd = 'quit' ifTrue: [
            isGameOver := true.
            isUnknown := false
        ].
	
	    cmd = 'w' ifTrue: [
		self move: 'w'.
		isUnknown := false
	    ].
	    
	    cmd = 'n' ifTrue: [
		self move: 'n'.
		isUnknown := false
	    ].
	    
	    cmd = 's' ifTrue: [
		self move: 's'.
		isUnknown := false
	    ].

	    cmd = 'e' ifTrue: [
		self move: 'e'.
		isUnknown := false
	    ].

	    cmd = 'quest' ifTrue: [
		self printQuest.
		isUnknown := false
	    ].

        cmd = 'bag' ifTrue: [
        self printLines: #('Your equipment:').
        eq do: [ :key |
            Transcript show: '  - ', key; cr.
        ].
        isUnknown := false
        ].

        isUnknown ifTrue: [
        self printLines: #('Unknown command.' '')
        ].
        ].
    ]
]

g := Game new.
g run.
