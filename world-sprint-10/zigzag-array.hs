import Control.Applicative ((<$>))

solve :: [Int] -> Int
solve (a1:a2:a3:as)
  | a1 < a2 && a2 > a3 = solve (a2:a3:as)
  | a1 > a2 && a2 < a3 = solve (a2:a3:as)
  | a1 < a2 && a2 < a3 = 1 + solve (a1:a3:as)
  | a1 > a2 && a2 > a3 = 1 + solve (a1:a3:as)
  | otherwise          = error "unexpected"
solve _ = 0

main :: IO ()
main = do
  _ <- getLine
  a <- map read . words <$> getLine
  putStrLn . show $ solve a