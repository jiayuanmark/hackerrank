import Control.Applicative
import Data.List (splitAt)
import Data.Maybe (catMaybes)

minCycle :: [Int] -> Int
minCycle l
  = let [a, b, c, d, e, f] = l
    in minimum [ e + d + a, a + b + c + d, f + a + b ]

solve :: [Int] -> Int
solve l = minimum . catMaybes . map try $ [0..length l - 1]
  where try p = case dropWhile (\d -> minCycle (mutate p d) < 0) [0..100] of
          []    -> Nothing
          (s:_) -> Just s
        mutate p d = let (lhs, r:rhs) = splitAt p l
                     in lhs ++ (r+d):rhs

main :: IO ()
main = do
  input <- map read . words <$> getLine
  putStrLn . show . solve $ input
