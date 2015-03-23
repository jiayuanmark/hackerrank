import Control.Applicative

cancel :: Int -> [Int] -> Bool
cancel k arr = (>) k . length $ filter (<= 0) arr

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  [_, k] <- map read . words <$> getLine
  arr    <- map read . words <$> getLine
  case (cancel k arr) of
    True -> putStrLn "YES"
    _    -> putStrLn "NO"
  solve $! (t-1)

main :: IO ()
main = do
  t <- read <$> getLine
  solve t
