import Control.Applicative
import Control.Monad
import Data.Function (on)
import Data.Tuple (swap)
import qualified Data.List as L

main :: IO ()
main = do
  n   <- read <$> getLine
  pts <- forM [1..n] $ \_ -> do
    [x, y] <- map read . words <$> getLine
    return (x, y)
  case solve pts of
    True -> putStrLn "YES"
    _    -> putStrLn "NO"

solve :: [(Integer, Integer)] -> Bool
solve pts =
  let spts = L.sortBy cmp pts
  in check spts
  where
    lo = L.minimumBy (compare `on` swap) pts
    cmp l r
      | ccw' == 0 = (dst lo l) `compare` (dst lo r)
      | ccw' >  0 = GT
      | otherwise = LT
      where ccw' = ccw lo l r
    dst (x,y) (u,v)       = sqrt . fromIntegral $ (x - u) ^ 2 + (y - v) ^ 2
    ccw (a,b) (x,y) (u,v) = (y-b) * (u-x) - (x-a) * (v-y)
    check (a:b:c:[])  = (ccw a b c) > 0
    check (a:b:c:ps)
      | ccw a b c > 0 = True
      | otherwise     = check (b:c:ps)
