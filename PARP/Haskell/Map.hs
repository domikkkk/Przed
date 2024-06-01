module Map where
data Direction = North | South | East | West deriving (Show, Eq)

type Location = String
type Connection = (Location, Direction, Location)
type Desc = (Location, String)
type Description = [Desc]
type WorldMap = [Connection]
type Monster = (Location, String, Int)
type Monsters = [Monster]
type RandomMonsters = [Monster]
type LvlUp = (Location, Int)
type LvlUps = [LvlUp]
type Key = (Location, String)
type Keys = [Key]
type Character = (Location, String)
type Characters = [Character]

worldMap :: WorldMap
worldMap =
  [ ("a1", East, "a2"),
    ("a1", South, "b1"),
    ("a2", West, "a1"),
    ("a2", East, "a3"),
    ("a2", South, "b2"),
    ("a3", West, "a2"),
    ("a3", East, "a4"),
    ("a3", South, "b3"),
    ("a4", West, "a3"),
    ("a5", East, "a6"),
    ("a5", South, "b5"),
    ("a6", West, "a5"),
    ("a6", South, "b6"),
    ("a7", West, "a6"),
    ("b1", South, "c1"),
    ("b1", North, "a1"),
    ("b1", East, "b2"),
    ("b2", North, "a2"),
    ("b2", West, "b1"),
    ("b2", East, "b3"),
    ("b2", South, "c2"),
    ("b3", North, "a3"),
    ("b3", West, "b2"),
    ("b3", South, "c3"),
    ("b5", North, "a5"),
    ("b5", East, "b6"),
    ("b6", North, "a6"),
    ("b6", East, "b7"),
    ("b6", West, "b5"),
    ("b6", South, "c6"),
    ("b7", South, "c7"),
    ("b7", West, "b6"),
    ("c1", North, "b1"),
    ("c1", East, "c2"),
    ("c1", South, "d1"),
    ("c2", North, "b2"),
    ("c2", West, "c1"),
    ("c2", East, "c3"),
    ("c2", South, "d2"),
    ("c3", North, "b3"),
    ("c3", West, "c2"),
    ("c3", South, "d3"),
    ("c6", North, "b6"),
    ("c6", East, "c7"),
    ("c6", South, "d6"),
    ("c7", North, "b7"),
    ("c7", West, "c6"),
    ("c7", South, "d7"),
    ("d1", North, "c1"),
    ("d1", East, "d2"),
    ("d1", South, "e1"),
    ("d2", North, "c2"),
    ("d2", West, "d1"),
    ("d2", East, "d3"),
    ("d2", South, "e2"),
    ("d3", North, "c3"),
    ("d3", West, "d2"),
    ("d3", East, "d4"),
    ("d3", South, "e3"),
    ("d4", South, "e4"),
    ("d4", West, "d3"),
    ("d6", North, "c6"),
    ("d6", South, "e6"),
    ("d6", East, "d7"),
    ("d7", North, "c7"),
    ("d7", West, "d6"),
    ("d7", South, "e7"),
    ("e1", North, "d1"),
    ("e1", South, "f1"),
    ("e1", East, "e2"),
    ("e2", North, "d2"),
    ("e2", West, "e1"),
    ("e2", East, "e3"),
    ("e2", South, "f2"),
    ("e3", North, "d3"),
    ("e3", West, "e2"),
    ("e3", East, "e4"),
    ("e4", North, "d4"),
    ("e4", West, "e3"),
    ("e4", East, "e5"),
    ("e5", West, "e4"),
    ("e5", East, "e6"),
    ("e6", North, "d6"),
    ("e6", West, "e5"),
    ("e6", South, "f6"),
    ("e6", East, "e7"),
    ("e7", North, "d7"),
    ("e7", West, "e6"),
    ("e7", South, "f7"),
    ("f1", North, "e1"),
    ("f1", East, "f2"),
    ("f1", South, "g1"),
    ("f2", North, "e2"),
    ("f2", West, "f1"),
    ("f2", South, "g2"),
    ("f6", North, "e6"),
    ("f6", South, "g6"),
    ("f6", East, "f7"),
    ("f7", North, "e7"),
    ("f7", South, "g7"),
    ("f7", West, "f6"),
    ("g1", North, "f1"),
    ("g1", East, "g2"),
    ("g2", North, "f2"),
    ("g2", West, "g1"),
    ("g4", East, "g5"),
    ("g5", East, "g6"),
    ("g6", North, "f6"),
    ("g6", West, "g5"),
    ("g6", East, "g7"),
    ("g7", North, "f7"),
    ("g7", West, "g6")
  ]

descriptions :: Description
descriptions = [
    ("a1", "Forest"),
    ("a2", "Forest"),
    ("a3", "Mountains"),
    ("a4", "Mountains"),
    ("a5", "Mountains"),
    ("a6", "Valley"),
    ("a7", "Abandoned house"),
    ("b1", "Forest"),
    ("b2", "Forest"),
    ("b3", "Forest"),
    ("b5", "Cave"),
    ("b6", "Valley"),
    ("b7", "Mountains"),
    ("c1", "Forest"),
    ("c2", "Forest"),
    ("c3", "Forest"),
    ("c6", "Valley"),
    ("c7", "Valley"),
    ("d1", "Savanna"),
    ("d2", "Forest"),
    ("d3", "Forest"),
    ("d4", "Aynor Village"),
    ("d6", "Savanna"),
    ("d7", "Savanna"),
    ("e1", "Savanna"),
    ("e2", "Savanna"),
    ("e3", "Fields"),
    ("e4", "Fields"),
    ("e5", "Bridge"),
    ("e6", "Swamp"),
    ("e7", "Swamp"),
    ("f1", "Desert"),
    ("f2", "Desert"),
    ("f6", "Swamp"),
    ("f7", "Swamp"),
    ("g1", "Temple"),
    ("g2", "Desert"),
    ("g4", "Exeter Village"),
    ("g5", "Swamp"),
    ("g6", "Swamp"),
    ("g7", "Swamp")
  ]

monsters :: Monsters
monsters = [
    ("a1", "MiniBoss - Druid", 2),
    ("a7", "FINAL BOSS - Ephemeral Phantom", 5),
    ("b5", "MiniBoss - Goblin", 4),
    ("c2", "Elf", 1),
    ("f2", "Hermit", 1),
    ("g1", "MiniBoss - Undead Priest", 3),
    ("a4", "River spirit", 0)
	]

randomMonsters :: RandomMonsters
randomMonsters = [
	("a2", "Wolf", 1),
	("a3", "Elf", 1),
	("b2", "Elf", 1),
  ("b3", "Wolf", 1),
	("b6", "Goblin", 1),
	("c1", "Wolf", 1),
	("c3", "Elf", 1),
	("c6", "Goblin", 1),
	("d1", "Ocelot", 1),
	("d3", "Wolf", 1),
	("d6", "Ocelot", 1),
	("d7", "Ocelot", 1),
  ("e2", "Lion", 1),
	("e4", "Goblin", 1),
  ("e6", "Drowned", 1),
	("f1", "Hermit", 1),
	("f6", "Drowned", 1),
	("f7", "Drowned", 1),
	("g5", "Naiad", 1),
  ("g7", "Drowned", 1)
	]

lvlups :: LvlUps
lvlups = [
  	("c2", 1),
  	("f2", 1),
  	("a4", 1),
  	("g4", 1)
	]

keys :: Keys
keys = [
	("a1", "Heartwood Key"),
  	("g1", "Divine Sigil Key"),
  	("b5", "Stoneheart Key")
	]

characters :: Characters
characters = [
 	("d4", "Jake")
	]