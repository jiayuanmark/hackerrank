import Control.Applicative
import qualified Data.List as L

solve :: [Int] -> [Int] -> Int -> Int
solve [] _ _ = 0
solve _ [] _ = 0
solve boy@(b:bs) girl@(g:gs) k
  | b < (g - k) = solve bs girl k
  | b > (g + k) = solve boy gs k
  | otherwise   = 1 + solve bs gs k

main :: IO ()
main = do
  [_, k] <- map read . words <$> getLine
  boys   <- map read . words <$> getLine
  girls  <- map read . words <$> getLine
  let sboys = L.sort boys
  let sgirls = L.sort girls
  putStrLn . show $ solve sboys sgirls k