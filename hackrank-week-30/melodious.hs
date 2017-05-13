import Control.Applicative ((<$>))
import Control.Monad (forM_)

candidate :: String
candidate = "bcdfghjklmnpqrstvwxz"

vowels :: String
vowels = "aeiou"

gen1 :: Int -> [String]
gen1 1 = map (\x -> [x]) vowels
gen1 n = do
  v <- vowels
  vs <- gen2 (n-1)
  return (v : vs)

gen2 :: Int -> [String]
gen2 1 = map (\x -> [x]) candidate
gen2 n = do
  c <- candidate
  cs <- gen1 (n-1)
  return (c : cs)

main :: IO ()
main = do
  n <- read <$> getLine
  forM_ (gen1 n) putStrLn
  forM_ (gen2 n) putStrLn