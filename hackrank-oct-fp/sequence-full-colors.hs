import qualified Data.List as L
import Control.Monad

fullColor :: String -> Bool
fullColor s =
  (count 'R' == count 'G') && (count 'Y' == count 'B') && (prefix 'R' 'G' 0 0 s) && (prefix 'Y' 'B' 0 0 s)
  where
    count c = L.foldl' (\x y -> if y == c then x+1 else x) 0 s
    prefix s1 s2 c1 c2 [] = True
    prefix s1 s2 c1 c2 (s:ss)
      | s1 == s = (abs (c1+1-c2) <= 1) && prefix s1 s2 (c1+1) c2 ss
      | s2 == s = (abs (c1-1-c2) <= 1) && prefix s1 s2 c1 (c2+1) ss
      | otherwise = prefix s1 s2 c1 c2 ss

main :: IO ()
main = do
  t <- getLine
  forM_ [1..(read t)] $ \_ ->
    do
      color <- getLine
      putStrLn $ show (fullColor color)
