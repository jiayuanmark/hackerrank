import Control.Applicative
import Control.Monad
import qualified Data.List as L

subarray :: [Int] -> (Int, (Int,Int))
subarray arr = (v, (-l,-r))
  where
    ((v,l),r)        = L.foldl1' max (zip larr [(-1),(-2)..]) 
    larr             = map (\(v,i) -> (v,-i)) $ tail $ scanl go (0,1) (zip arr [1..])
    go (x,xi) (y,yi) = if (x+y) > 0 then (x+y,xi) else (0,yi+1)

solve :: Int -> [Int] -> IO ()
solve k arr
  | k == 0 || v == 0 = return () 
  | otherwise        = (putStrLn (show v)) >> solve (k-1) newarr
  where
    (v, (l,r)) = subarray arr
    newarr     = (take (l-1) arr) ++ (drop r arr)

main :: IO ()
main = do
  [_, k] <- map read . words <$> getLine
  arr    <- map read . words <$> getLine
  solve k arr