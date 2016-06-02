import Control.Applicative

solve :: [Int] -> Int -> Int -> Int
solve a n k
  = length . filter p $ [ (i,j) | i <- [0..n-1], j <- [0..n-1], i < j ]
  where p (i,j) = ((a !! i) + (a !! j)) `mod` k == 0

main :: IO ()
main = do
  [n, k] <- map read . words <$> getLine
  a      <- map read . words <$> getLine
  putStrLn . show $ solve a n k
