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
solve s@(p:ps) = abs . sum . map (uncurry area) . zip s $ ps ++ [p]
  where
    area (x,y) (u,v) = (/ 2) . fromIntegral $ (x + u) * (v - y)
