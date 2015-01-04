import Control.Applicative

solve :: Int -> IO ()
solve 0 = return ()
solve t = do
  n <- read <$> getLine
  putStrLn . show $ quot (n * (3 * n - 1))  2 
  solve $! t-1

main :: IO ()
main = do
  t <- read <$> getLine
  solve t