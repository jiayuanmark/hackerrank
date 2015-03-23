import Control.Applicative
import qualified Data.List as L

subarray :: [Integer] -> Integer -> Integer
subarray arr m = L.foldl1' max $ scanl go 0 arr
  where go x y = let old = (x+y) `mod` m
                     new = y `mod` m
                 in max old new

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  [_, m] <- map read . words <$> getLine
  arr    <- map read . words <$> getLine
  putStrLn . show $ subarray arr m
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t