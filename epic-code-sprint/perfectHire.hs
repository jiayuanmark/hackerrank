import Control.Applicative
import qualified Data.List as L

solve :: Int -> Int -> [Int] -> Int
solve p x as = snd . L.foldl1' max $ zip val [1..]
  where val = zipWith (*) [p,(p-x)..0] as

main :: IO ()
main = do
  [_, p, x] <- map read . words <$> getLine
  as        <- map read . words <$> getLine
  putStrLn . show $ solve p x as