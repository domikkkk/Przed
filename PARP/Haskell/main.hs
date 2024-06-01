module Main where

import Map
import Data.List (find)
import Control.Monad.State
import Control.Monad
import Control.Monad.Trans
import Control.Monad.Identity
import System.Random
import System.Exit (exitSuccess)
import Data.Maybe (isJust, fromJust, fromMaybe, maybe, isNothing)

data GameState = GameState
  {currentLocation :: Location,
   playerWeaponLvl :: Int,
   monstersActual :: Monsters,
   monstersRandom :: RandomMonsters,
   currentQuest :: String,
   equipment :: [Key],
   worldMapActual :: WorldMap}

instructionsText :: [String]
instructionsText = [
    "Available commands are:",
    "",
    "instructions  -- to see these instructions.",
    "quit          -- to end the game and quit.",
    "w             -- go west.",
    "e             -- go east.",
    "n             -- go north.",
    "s             -- go south.",
    "bag           -- see your equipment",
    "quest         -- print current quest.",
    "talk <person> -- talk to person in location",
    ""
    ]

printLines :: [String] -> IO ()
printLines xs = putStr (unlines xs)

printInstructions :: IO ()
printInstructions = printLines instructionsText

readCommand :: IO String
readCommand = do
    putStr "\n> "
    getLine

death :: StateT GameState IO ()
death = do
    currentState <- get
    put currentState { currentLocation ="d4"}
    lift $ putStrLn $ ""
    lift $ putStrLn $ "Local medic has found your body..."
    lift $ putStrLn $ ""
    lift $ putStrLn $ ""
    look
look :: StateT GameState IO ()
look = do
    currentState <- get
    let loc = currentLocation currentState
    let weaponLvl = playerWeaponLvl currentState
    lift $ putStrLn $ "Your level: " ++ show weaponLvl
    case lookup loc descriptions of
        Just description -> lift $ putStrLn $ "You are in " ++ description
        Nothing -> lift $ putStrLn "Description not found for the current location."
    checkIfInExeter
    liftIO $ listCharactersAt loc characters
    let monsterInfo = checkMonster loc (monstersActual currentState)
    if isJust monsterInfo
        then do
            let (monsterName, monsterLevel) = fromMaybe ("Empty", 0) monsterInfo
            lift $ putStrLn $ "A wild " ++ monsterName ++ " [lvl " ++ show monsterLevel ++ "] appears!"
            monsterDefeated <- combat (monsterName, monsterLevel) weaponLvl
            if monsterDefeated
                then do
                    when (monsterName == "FINAL BOSS - Ephemeral Phantom") $ do
                        lift $ putStrLn $ "\nYOU FINISHED A GAME. CONGRATULATIONS!\n\n\n"
                        liftIO exitSuccess
                    let addLvl = checkLvlUp loc lvlups
                    modify (\s -> execState (updateWeaponLvl (playerWeaponLvl currentState + addLvl)) s)
                    modify (\s -> execState (removeMonster loc) s)
                    modify (\s -> execState (addKeyIfInLocation keys) s)
                    currentState <- get
                    let havekeys = haveAllKeys keys (equipment currentState)
                    -- liftIO $ putStrLn $ "Length of keys: " ++ show (length (equipment currentState))
                    when (havekeys && (currentQuest currentState) == "Collect 3 key fragments.") $ do
                        let newConnection = ("a6", East, "a7")
                        modify (\s -> execState (addConnection newConnection) s)
                        changeQuest "Talk to Jake in Anyor."
            else do
                death
                return ()
    else do
        shouldSpawnMonster <- liftIO $ randomRIO (1, 10 :: Int)
        when (shouldSpawnMonster <= 3) $ do
            let monsterInfo = checkMonster loc (monstersRandom currentState)
            if isJust monsterInfo
                then do
                    let (monsterName, _) = fromMaybe ("Empty", 0) monsterInfo
                    let levels = [1, 1, 1, 1, 1, 2, 2, 3, 4, 5]
                    idx <- liftIO $ randomRIO (0, 9 :: Int)
                    let monsterLevel = levels !! idx
                    lift $ putStrLn $ "A wild " ++ monsterName ++ " [lvl " ++ show monsterLevel ++ "] appears!"
                    monsterDefeated <- combat (monsterName, monsterLevel) weaponLvl
                    when (not monsterDefeated) $ do
                        death
                        return ()
                    return()
            else do
                lift $ return ()

go :: Direction -> Location -> [Connection] -> Location
go dir loc map =
    case dir of
        North -> case find (\(l, d, l') -> l == loc && d == North) map of
                    Just (_, _, newLoc) -> newLoc
                    Nothing -> loc
        South -> case find (\(l, d, l') -> l == loc && d == South) map of
                    Just (_, _, newLoc) -> newLoc
                    Nothing -> loc
        East -> case find (\(l, d, l') -> l == loc && d == East) map of
                    Just (_, _, newLoc) -> newLoc
                    Nothing -> loc
        West -> case find (\(l, d, l') -> l == loc && d == West) map of
                    Just (_, _, newLoc) -> newLoc
                    Nothing -> loc

n :: State GameState String
n = do
    currentState <- get
    let worldMapActualValue = worldMapActual currentState
    let newLocation = go North (currentLocation currentState) worldMapActualValue
    put (currentState { currentLocation = newLocation })
    return newLocation

s :: State GameState String
s = do
    currentState <- get
    let worldMapActualValue = worldMapActual currentState
    let newLocation = go South (currentLocation currentState) worldMapActualValue
    put (currentState { currentLocation = newLocation })
    return newLocation

e :: State GameState String
e = do
    currentState <- get
    let worldMapActualValue = worldMapActual currentState
    let newLocation = go East (currentLocation currentState) worldMapActualValue
    put (currentState { currentLocation = newLocation })
    return newLocation

w :: State GameState String
w = do
    currentState <- get
    let worldMapActualValue = worldMapActual currentState
    let newLocation = go West (currentLocation currentState) worldMapActualValue
    put (currentState { currentLocation = newLocation })
    return newLocation

checkMonster :: Location -> [Monster] -> Maybe (String, Int)
checkMonster currentLocation monsters =
    case filter (\(monsterLocation, _, _) -> currentLocation == monsterLocation) monsters of
        [] -> Nothing
        [(_, name, lvl)] -> Just (name, lvl)

combat :: (String, Int) -> Int -> StateT GameState IO Bool
combat (name, monsterLvl) playerWeaponLvl = do
    lift $ putStrLn $ "You are battling " ++ name
    if playerWeaponLvl >= monsterLvl
        then do
            lift $ putStrLn $ "You have defeated " ++ name
            return True
        else do
            lift $ putStrLn $ "You were defeated by " ++ name
            return False

removeMonster :: String -> State GameState ()
removeMonster monsterLoc = do
    currentState <- get
    let currentMonsters = monstersActual currentState
        newMonsters = filter (\(loc, _, _) -> loc /= monsterLoc) currentMonsters
    put currentState { monstersActual = newMonsters }

updateWeaponLvl :: Int -> State GameState ()
updateWeaponLvl newLvl = do
    currentState <- get
    put currentState { playerWeaponLvl = newLvl }

checkLvlUp :: Location -> LvlUps -> Int
checkLvlUp currentLocation lvlups =
    case filter (\(lvlUpLoc, _) -> currentLocation == lvlUpLoc) lvlups of
        [] -> 0
        [(_, addLvl)] -> addLvl


haveAllKeys :: Keys -> Keys -> Bool
haveAllKeys keys1 keys2 = length keys1 == length keys2


addKeyIfInLocation :: Keys -> State GameState ()
addKeyIfInLocation keys = do
    currentState <- get
    let currentLoc = currentLocation currentState
        keyincurrLoc = filter (\(loc, _) -> loc == currentLoc) keys
    put currentState {equipment = equipment currentState ++ keyincurrLoc}


addConnection :: Connection -> State GameState ()
addConnection connection = do
    currentState <- get
    let updatedMap = connection : worldMapActual currentState
    put currentState { worldMapActual = updatedMap }


formatKey :: Key -> String
formatKey (_, keyName) = "- " ++ keyName

getFirstWord :: String -> String
getFirstWord str = case words str of
    (firstWord:_) -> firstWord
    _ -> ""

getSecondWord :: String -> String
getSecondWord str =
    case words str of
        (_:second:_) -> second
        _ -> ""

gameLoop :: StateT GameState IO ()
gameLoop = do
    look
    cmd <- lift readCommand
    currentState <- get
    case getFirstWord cmd of
        "instructions" -> do
            lift printInstructions
            gameLoop
        "n" -> do
            -- newLoc <- n
            let newLoc = evalState n currentState
            modify (\s -> execState n s)
            if currentLocation currentState == newLoc then
                lift $ putStrLn "You can't go that way!"
                else
                    lift $ putStrLn $ "You are now at location " ++ newLoc
            gameLoop
        "w" -> do
            -- newLoc <- w
            let newLoc = evalState w currentState
            modify (\s -> execState w s)
            if currentLocation currentState == newLoc then
                lift $ putStrLn "You can't go that way!"
                else
                    lift $ putStrLn $ "You are now at location " ++ newLoc
            gameLoop
        "s" -> do
            -- newLoc <- s
            let newLoc = evalState s currentState
            modify (\x -> execState s x)
            if currentLocation currentState == newLoc then
                lift $ putStrLn "You can't go that way!"
                else
                    lift $ putStrLn $ "You are now at location " ++ newLoc
            gameLoop
        "e" -> do
            -- newLoc <- e
            let newLoc = evalState e currentState
            modify (\s -> execState e s)
            if currentLocation currentState == newLoc then
                lift $ putStrLn "You can't go that way!"
                else
                    lift $ putStrLn $ "You are now at location " ++ newLoc
            gameLoop
        "bag" -> do
            lift $ putStrLn "\nMy equipment:"
            lift $ mapM_ (putStrLn . formatKey) (equipment currentState)
            lift $ putStrLn ""
            gameLoop
        "quest" -> do
            printCurrentQuest
            gameLoop
        "talk" -> do
            talk (getSecondWord cmd)
            gameLoop
        "quit" -> return ()
        _ -> do
            lift $ printLines ["Unknown command.", ""]
            gameLoop

changeQuest :: String -> StateT GameState IO ()
changeQuest newQuest = do
    currentState <- get
    lift $ putStrLn $ "\nQUEST FINISHED: " ++ currentQuest currentState ++ "\n"
    put currentState { currentQuest = newQuest}
    printNewQuest

printNewQuest :: StateT GameState IO ()
printNewQuest = do
    currentState <- get
    lift $ putStrLn $ ""
    lift $ putStrLn $ "NEW QUEST ADDED: " ++ currentQuest currentState
    lift $ putStrLn $ ""

printCurrentQuest :: StateT GameState IO ()
printCurrentQuest = do
    currentState <- get
    lift $ putStrLn $ "CURRENT QUEST: " ++ currentQuest currentState

listCharactersAt :: Location -> Characters -> IO ()
listCharactersAt _ [] = return ()
listCharactersAt loc ((l, name):xs) =
    if loc == l
        then do
            putStrLn $ "Characters present: " ++ name
            return ()
        else listCharactersAt loc xs

talk :: String -> StateT GameState IO ()
talk name = do
    currentState <- get
    let havekeys = haveAllKeys keys (equipment currentState)
    if name == "Jake" && havekeys
        then do
            lift $ putStrLn $ "So it is true. You need to prepare. Find Exeter to get a better weapon."
            changeQuest "Find Exeter to get a better weapon."
            let newConnection = ("g5", West, "g4")
            modify (\s -> execState (addConnection newConnection) s)
            return ()
        else do
            lift $ putStrLn $ "Cannot talk to him!"
            return ()

checkIfInExeter :: StateT GameState IO ()
checkIfInExeter = do
    currentState <- get
    let loc = currentLocation currentState
    if loc == "g4" && currentQuest currentState == "Find Exeter to get a better weapon." then do
        changeQuest "Kill Empheral Phantom."
        let addLvl = checkLvlUp loc lvlups
        modify (\s -> execState (updateWeaponLvl (playerWeaponLvl currentState + addLvl)) s)
    else return ()

main :: IO ()
main = do
    let state = GameState {currentLocation="d4", playerWeaponLvl=1, monstersActual=monsters,
    monstersRandom=randomMonsters, currentQuest = "Collect 3 key fragments.", equipment = [], worldMapActual=worldMap}
    putStrLn "In a realm veiled by ancient lore, three guardians protected fragments of a mysterious key."
    putStrLn "Druid guarded the forest, the Undead Priest watched over the temple, and a formidable Goblin held the key fragment in treacherous caves."
    putStrLn "Legends whispered of an elusive entity, the Ephemeral Phantom, residing in the abandoned house, said to hold the power to shape the realm's destiny."
    putStrLn "Only a brave soul could confront this being and determine the realm's fate."

    putStrLn ""
    putStrLn $ "NEW QUEST ADDED: " ++ "Collect 3 key fragments."
    putStrLn ""
    printInstructions
    evalStateT gameLoop state