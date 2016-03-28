{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import Data.Attoparsec.ByteString.Char8 (decimal, sepBy, space, parseOnly)
import qualified Data.ByteString.Char8 as C
import qualified Data.Map.Strict as M

data Heap = H { rank  :: {-# UNPACK #-} !Int
              , elem  :: {-# UNPACK #-} !Int
              , left  :: Heap
              , right :: Heap
              }
          | E
          deriving (Eq, Show)

empty :: Heap
empty = E

rank' :: Heap -> Int
rank' E = 0
rank' h = rank h

makeHeap :: Int -> Heap -> Heap -> Heap
makeHeap n l r =
  let rankL = rank' l
      rankR = rank' r
  in if rankL >= rankR
     then H (rankR + 1) n l r
     else H (rankL + 1) n r l

merge :: Heap -> Heap -> Heap
merge h E = h
merge E h = h
merge h1@(H _ x l1 r1) h2@(H _ y l2 r2)
  | x <= y    = makeHeap y l2 (merge h1 r2)
  | otherwise = makeHeap x l1 (merge r1 h2)

findMax :: Heap -> Int
findMax E           = error "empty heap"
findMax (H _ x _ _) = x

deleteMax :: Heap -> Heap
deleteMax E           = error "empty heap"
deleteMax (H _ _ l r) = merge l r

insert :: Int -> Heap -> Heap
insert x = merge (H 1 x E E)

parseInts :: C.ByteString -> [Int]
parseInts s =
  case (parseOnly p s) of
    Left  e -> error e
    Right r -> r
  where p = decimal `sepBy` space

solve :: Int -> M.Map Int Heap -> IO ()
solve 0 _ = return ()
solve !q !m = do
  qry <- parseInts <$> C.getLine
  m'  <- solve' qry m
  solve (q-1) $! m'
  where
    solve' (1:x:_) mp = do
      let h = M.findWithDefault E x mp
      putStrLn . show $ findMax h
      return mp
    solve' (2:x:_) mp =
      return $ M.adjust deleteMax x mp
    solve' (3:x:y:_) mp =
      return $ M.adjust (insert y) x mp
    solve' (4:x:y:_) mp = do
      let h = M.findWithDefault E y mp
      return $ M.insertWith merge x h mp

main :: IO ()
main = do
  [n, q] <- parseInts <$> C.getLine
  solve q $ M.fromList $ zip [1..n] (replicate n E)
