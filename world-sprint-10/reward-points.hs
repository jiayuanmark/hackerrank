import Control.Applicative ((<$>))

solve :: [Int] -> Int
solve = sum . map (\m -> min 100 (10 * m))

main :: IO ()
main = do
  m <- map read . words <$> getLine
  putStrLn . show $ solve m