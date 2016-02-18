import Control.Applicative
import qualified Data.List as L

type Point = (Integer, Integer)

turn1 :: Integer -> Point -> Point
turn1 n (x,y) = (x+n,y)

turn2 :: Integer -> Point -> Point
turn2 n (x,y) = (x,y+n)

turn3 :: Integer -> Point -> Point
turn3 n (x,y) = (x-n,y)

turn4 :: Integer -> Point -> Point
turn4 n (x,y) = (x,y-n)

calc :: Integer -> Point
calc n = let iv = n `div` 4
             pt = (-2 * iv, -2 * iv)
             op = L.zipWith ($) [turn1, turn2, turn3, turn4] [(iv * 4 + 1)..n]
         in L.foldl' (flip ($)) pt op

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  n <- read <$> getLine
  let (x, y) = calc n
  putStrLn $ (show x) ++ " " ++ (show y)
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t