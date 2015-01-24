import Control.Applicative
import qualified Data.List as L

data Tree = Branch { val   :: Int
                   , range :: (Int,Int)
                   , left  :: Tree
                   , right :: Tree
                   }
          | Leaf   { val   :: Int
                   , range :: (Int, Int)
                   } deriving (Show, Eq)

split :: (Int,Int) -> Int
split (l,r) = (l+r) `div` 2

buildTree :: [Int] -> (Int,Int) -> Tree
buildTree arr rng@(l,r)
  | l == r    = Leaf (head arr) rng
  | otherwise = Branch { val   = min (val ltree) (val rtree)
                       , range = rng
                       , left  = ltree
                       , right = rtree
                       }
  where
    mid         = split rng
    (larr,rarr) = L.splitAt (mid-l+1) arr
    ltree       = buildTree larr (l,mid)
    rtree       = buildTree rarr (mid+1,r)

queryTree :: Tree -> (Int, Int) -> Int
queryTree (Leaf v _) _ = v
queryTree (Branch v rg lft rht) rng@(l,r)
  | rng == rg  = v
  | r <= mid   = queryTree lft rng
  | l > mid    = queryTree rht rng
  | otherwise  = min lquery rquery
  where
    mid    = split rg
    lquery = queryTree lft (l,mid)
    rquery = queryTree rht (mid+1,r)

solve :: Tree -> Int -> IO ()
solve _ 0 = return ()
solve t m = do
  [l, r] <- map read . words <$> getLine
  putStrLn . show $ queryTree t (l,r)
  solve t $! (m-1) 

main :: IO ()
main = do
  [n, m] <- map read . words <$> getLine
  arr    <- map read . words <$> getLine
  let tree = buildTree arr (0,n-1)
  solve tree m

