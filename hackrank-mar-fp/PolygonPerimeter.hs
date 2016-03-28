import Control.Applicative
import Control.Monad
import Data.Function (on)
import Data.Tuple (swap)
import qualified Data.List as L

main :: IO ()
main = do
  n   <- read <$> getLine
  pts <- forM [1..n] $ \_ -> do
    [x, y] <- map read . words <$> getLine
    return (x, y)
  putStrLn . show $ solve pts

solve :: [(Integer, Integer)] -> Double
solve s@(p:ps) = sum . map (uncurry dst) . zip s $ ps ++ [p]
  where dst (x,y) (u,v) = sqrt . fromIntegral $ (x - u) ^ 2 + (y - v) ^ 2
