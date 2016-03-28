import Control.Applicative ((<$>), (*>))
import Control.Monad (forM, foldM_)
import Data.Either (rights)
import Data.List (splitAt)
import Text.Parsec
import Text.Parsec.String

data Ops = Change Int
         | Print
         | VisitLeft
         | VisitRight
         | VisitParent
         | VisitChild Int
         | InsertLeft Int
         | InsertRight Int
         | InsertChild Int
         | Delete
         deriving (Eq, Show)

data Tree = Tree { val :: Int
                 , chd :: [Tree]
                 }
                 deriving (Eq, Show)

data Focus = Focus { lhs :: [Tree]
                   , cur :: Tree
                   , rhs :: [Tree]
                   }
                   deriving (Eq, Show)

data Crumb = Crumb { pval :: Int
                   , lfoc :: [Tree]
                   , rfoc :: [Tree]
                   }
                   deriving (Eq, Show)

type Zipper = (Focus, [Crumb])

num :: Parser Int
num = read <$> many1 digit

opsParser :: Parser Ops
opsParser = Change <$> (string "change " *> num) <|>
            string "print" *> return Print <|>
            try (string "visit left" *> return VisitLeft) <|>
            try (string "visit right" *> return VisitRight) <|>
            try (string "visit parent" *> return VisitParent) <|>
            VisitChild <$> (string "visit child " *> num) <|>
            try (InsertLeft <$> (string "insert left " *> num)) <|>
            try (InsertRight <$> (string "insert right " *> num)) <|>
            InsertChild <$> (string "insert child " *> num) <|>
            string "delete" *> return Delete

readInput :: IO [Ops]
readInput = do
  n <- read <$> getLine
  s <- forM [1..n] $ \_ -> getLine
  return . rights . map (parse opsParser "") $ s

newNode :: Int -> Tree
newNode n = Tree n []

focus :: Int -> [Tree] -> Focus
focus n nodes = Focus (reverse l) r rs
  where (l, r:rs) = splitAt (n-1) nodes

backout :: Focus -> [Tree]
backout (Focus l c r) = (reverse l) ++ (c:r)

moveLeft :: Focus -> Focus
moveLeft (Focus (l:ls) c r) = Focus ls l (c:r)
moveLeft _                  = error "cannot move left!"

moveRight :: Focus -> Focus
moveRight (Focus l c (r:rs)) = Focus (c:l) r rs
moveRight _                  = error "cannot move right!"

insertLeft :: Int -> Focus -> Focus
insertLeft n (Focus l c r) = Focus (newNode n:l) c r

insertRight :: Int -> Focus -> Focus
insertRight n (Focus l c r) = Focus l c (newNode n:r)

mutate :: (Focus -> Focus) -> Zipper -> Zipper
mutate g (f,z) = (g f, z)

execute :: Ops -> Zipper -> IO Zipper
execute (Change x) zp =
  return (mutate g zp)
  where g f@(Focus l c r) = case c of
          Tree _ cs -> Focus l (Tree x cs) r
execute Print zipper@(f, _) =
  let t = val (cur f)
  in putStrLn (show t) >> return zipper
execute VisitLeft zp =
  return (mutate moveLeft zp)
execute VisitRight zp =
  return (mutate moveRight zp)
execute VisitParent (f, Crumb p l r : cs) =
  return (Focus l (Tree p (backout f)) r, cs)
execute VisitParent _ =
  error "cannot move up!"
execute (VisitChild x) (Focus l c r, cs) =
  case c of
    Tree p chd -> return (focus x chd, Crumb p l r : cs)
execute (InsertLeft x) zp =
  return (mutate (insertLeft x) zp)
execute (InsertRight x) zp =
  return (mutate (insertRight x) zp)
execute (InsertChild x) zp =
  return (mutate insertChild zp)
  where insertChild (Focus l c r) = case c of
          Tree v cs -> Focus l (Tree v (newNode x:cs)) r
execute Delete (Focus ll c rr, Crumb p l r : cs) =
  return ((Focus l (Tree p (reverse ll ++ rr)) r), cs)

start :: Zipper
start = (Focus [] (newNode 0) [], [])

solve :: [Ops] -> IO ()
solve = foldM_ (flip execute) start

main :: IO ()
main = do
  ops <- readInput
  solve ops
