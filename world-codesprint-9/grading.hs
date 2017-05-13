import Control.Applicative ((<$>))
import Control.Monad

solve :: Int -> Int
solve g
  | g < 38    = g
  | gap < 3   = g + gap
  | otherwise = g
  where gap = 5 - (g `mod` 5)
 
main :: IO ()
main = do
  n <- read <$> getLine
  forM_ [1..n] $ \_ -> do
    grade <- read <$> getLine
    print (solve grade)