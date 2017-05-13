import Control.Applicative ((<$>))

solve :: Int -> String
solve 2 = "min(int, int)"
solve n = "min(int, " ++ (solve (n-1)) ++ ")"

main :: IO ()
main = do
  n <- read <$> getLine
  putStrLn (solve n)
