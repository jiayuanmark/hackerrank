import Control.Applicative
import Control.Monad
import qualified Data.Map as M

main :: IO ()
main = do
  t <- read <$> getLine
  forM_ [1..t] $ \_ -> solve

solve :: IO ()
solve = do
  n  <- read <$> getLine
  tp <- forM [1..n] $ \_ -> do
    [x, y] <- map read . words <$> getLine
    return (x, [y])
  let m = M.fromListWith (++) tp :: M.Map Int [Int]
  case all (\x -> length x == 1) (M.elems m) of
    True -> putStrLn "YES"
    _    -> putStrLn "NO"
