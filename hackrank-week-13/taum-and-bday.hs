import Control.Applicative

buy :: Integer -> Integer -> Integer -> Integer -> Integer -> Integer
buy b w x y z
  | x + z <= y = b * x + w * (x+z)
  | y + z <= x = b * (y+z) + w * y
  | otherwise  = b * x + w * y

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  [b, w]    <- map read . words <$> getLine
  [x, y, z] <- map read . words <$> getLine
  putStrLn $ show (buy b w x y z)
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t