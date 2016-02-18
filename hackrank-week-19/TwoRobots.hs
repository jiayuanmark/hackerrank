import Control.Applicative
import Control.Monad

solve :: IO ()
solve = do
  [m, n] <- map read . words <$> getLine
  query  <- forM [1..n] $ \_ -> do
    [x, y] <- map read . words <$> getLine
    return (x, y)
  putStrLn . show $ calc m query

calc :: Int -> [(Int,Int)] -> Int
calc = undefined

main :: IO ()
main = do
  t <- read <$> getLine
  forM_ [1..t] (const solve)
