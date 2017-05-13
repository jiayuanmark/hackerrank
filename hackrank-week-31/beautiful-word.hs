import Control.Applicative ((<*>), (<$>))

solve :: String -> Bool
solve w = not . any ((||) <$> s1 <*> s2) $ zip w (tail w)
  where s1 (a, b) = a == b
        s2 (a, b) = let l = "aeiouy" in (a `elem` l) && (b `elem` l)

main :: IO ()
main = do
  w <- getLine
  case (solve w) of
    True -> putStrLn "Yes"
    False -> putStrLn "No"