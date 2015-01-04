import Control.Applicative
import Data.Array (Array, accumArray, (!))
import Data.Maybe (fromJust)
import qualified Data.List as L

type Range = (Int, Int)

data Tree = Branch { range  :: Range
                   , upper  :: Int
                   , lower  :: Int
                   , lchild :: Tree
                   , rchild :: Tree
                   }
          | Leaf   { range  :: Range
                   , upper  :: Int
                   , lower  :: Int
                   }
          deriving (Show, Eq)

split :: (Int, Int) -> Int
split (l,r) = div (l+r) 2

buildTree :: Array Int Int -> Range -> Tree
buildTree arr rg@(l,r)
  | l == r = Leaf rg (arr ! l) (arr ! r)
  | otherwise = Branch { range = rg
             , upper = max (upper lft) (upper rht)
             , lower = min (lower lft) (lower rht)
             , lchild = lft
             , rchild = rht
             }
  where
    mid = split rg
    lft = buildTree arr (l,mid)
    rht = buildTree arr (mid+1,r)

processQuery :: Array Int Int -> Tree -> Int -> Int -> Int
processQuery arr tree d m = e - s + 1
  where
    lo = arr ! d
    (s,e) = fromJust $ queryTree tree lo (lo+m) d

leftJoin :: Maybe Range -> Maybe Range -> Maybe Range
leftJoin Nothing _ = Nothing
leftJoin lft Nothing = lft
leftJoin (Just lft) (Just rht)
  | 1 + snd lft == fst rht = Just (fst lft, snd rht)
  | otherwise = Just lft

rightJoin :: Maybe Range -> Maybe Range -> Maybe Range
rightJoin _ Nothing = Nothing
rightJoin Nothing rht = rht
rightJoin (Just lft) (Just rht)
  | 1 + snd lft == fst rht = Just (fst lft, snd rht)
  | otherwise = Just rht

queryRange :: Tree -> Int -> Int -> (Maybe Range -> Maybe Range -> Maybe Range) -> Maybe Range
queryRange (Leaf rg mx mi) lo hi _
  | mi >= lo && mx <= hi = Just rg
  | otherwise = Nothing
queryRange (Branch rg mx mi lch rch) lo hi join
  | mi >= lo && mx <= hi = Just rg
  | otherwise = join lres rres
  where
    lres = queryRange lch lo hi join
    rres = queryRange rch lo hi join

queryTree :: Tree -> Int -> Int -> Int -> Maybe (Int,Int)
queryTree (Leaf rg@(l,r) mx mi) lo hi idx
  | mi >= lo && mx <= hi = Just rg
  | otherwise = Nothing
queryTree (Branch rg@(l,r) mx mi lch rch) lo hi idx
  | mi >= lo && mx <= hi = Just rg
  | idx <= mid && ((snd . fromJust) lres == mid) = leftJoin lres $ queryRange rch lo hi leftJoin  
  | idx <= mid = lres
  | idx > mid && ((fst . fromJust) rres == mid+1) = rightJoin (queryRange lch lo hi rightJoin) $ rres
  | otherwise = rres 
  where
    mid = split rg
    lres = queryTree lch lo hi idx
    rres = queryTree rch lo hi idx

solve :: Int -> Array Int Int -> Tree -> IO ()
solve 0 _ _ = return ()
solve q arr tree = do
  [d, m] <- map read . words <$> getLine
  putStrLn . show $ processQuery arr tree d m
  solve (q-1) arr tree

main :: IO ()
main = do
  n <- read <$> getLine
  elems <- map read . words <$> getLine
  let arr = accumArray (+) 0 (0,n-1) $ zip [0..] elems
  q <- read <$> getLine
  solve q arr $ buildTree arr (0,n-1)

