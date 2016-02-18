import Control.Applicative

solve :: Int -> Int -> Int -> Int -> Int
solve a b c d =
  let lst = [ (aa, bb, cc, dd) | aa <- [1..a],
                                 bb <- [1..b],
                                 cc <- [1..c],
                                 dd <- [1..d],
                                 (abs (aa - bb)) `mod` 3 == 0,
                                 (bb + cc) `mod` 5 == 0,
                                 (aa * cc) `mod` 4 == 0,
                                 (gcd aa dd) == 1 ]
  in length lst


main :: IO ()
main = do
  [a, b, c, d] <- map read . words <$> getLine
  putStrLn . show $ solve a b c d