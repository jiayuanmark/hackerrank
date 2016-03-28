import Control.Applicative
import Data.List (foldl')
import qualified Data.Vector as V

type Range = (Int, Int)

data Tree = Leaf { val :: Integer
                 , rng :: Range
                 }
          | Tree { val :: Integer
                 , rng :: Range
                 , lhs :: Tree
                 , rhs :: Tree
                 }
          deriving (Eq, Show)

calcMid :: Range -> Int
calcMid (l,r) = (l + r) `div` 2

buildTree :: Range -> V.Vector Integer -> Tree
buildTree rg@(l,r) v
  | l == r    = Leaf (v V.! l) rg
  | otherwise = Tree (val lhs `min` val rhs) rg lhs rhs
  where
    mid = calcMid rg
    lhs = buildTree (l, mid)   v
    rhs = buildTree (mid+1, r) v

updateTree :: Int -> Tree -> Tree
updateTree = undefined

queryTree :: Range -> Tree -> Integer
queryTree _       (Leaf v _) = v
queryTree q@(l,r) (Tree v c@(l',r') lhs rhs)
  | q == c    = v
  | r <= mid  = queryTree q lhs
  | l > mid   = queryTree q rhs
  | otherwise = min lq rq
  where
    mid = calcMid c
    lq  = queryTree (l,mid)   lhs
    rq  = queryTree (mid+1,r) rhs

solve :: Integer -> V.Vector Integer -> Integer
solve n v = foldl' f 0 [ queryTree (a,b) tree `min` queryTree (c,d) tree
                         | a <- [1..n'], b <- [a..n'],
                           c <- [b+1..n'], d <- [c..n'] ]
  where
    n'      = fromIntegral n
    tree    = buildTree (1, n') v
    m       = (10^9 + 7)
    f acc e = (acc + e) `mod` m

main :: IO ()
main = do
  n <- read <$> getLine
  a <- map read . words <$> getLine
  let va = V.fromList (0 : a)
  putStrLn . show $ solve n va
