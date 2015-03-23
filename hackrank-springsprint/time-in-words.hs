import Control.Applicative

newtype NInt = NInt { int :: Int } deriving Eq

instance Show NInt where
  show val
    | v == 0  = "o' clock"
    | v == 1  = "one"
    | v == 2  = "two"
    | v == 3  = "three"
    | v == 4  = "four"
    | v == 5  = "five"
    | v == 6  = "six"
    | v == 7  = "seven"
    | v == 8  = "eight"
    | v == 9  = "nine"
    | v == 10 = "ten"
    | v == 11 = "eleven"
    | v == 12 = "twelve"
    | v == 13 = "thirteen"
    | v == 14 = modT v
    | v == 15 = "quarter"
    | v == 16 = modT v
    | v == 17 = modT v
    | v == 18 = "eighteen"
    | v == 19 = modT v
    | v == 20 = "twenty"
    | v == 30 = "half"
    | otherwise = modTw v
    where
      v       = int val
      modT  v = show (NInt (v `mod` 10)) ++ "teen"
      modTw v = "twenty " ++ (show (NInt (v `mod` 20)))


data Time = Time NInt NInt deriving Eq

instance Show Time where
  show (Time h m)
    | minutes <= 30 =
      case minutes of
        0  -> (show h) ++ " " ++ (show m)
        1  -> "one minute past " ++ (show h)
        30 -> (show m) ++ " past " ++ (show h)
        15 -> (show m) ++ " past " ++ (show h)
        _  -> (show m) ++ " minutes past " ++ (show h)
    | minutes == 45 = "quarter to " ++ nexthour
    | minutes == 59 = "one minute to " ++ nexthour
    | otherwise = (show (NInt (60 - minutes))) ++ " minutes to " ++ nexthour
    where
      minutes  = int m
      nexthour = (show (NInt (int h + 1)))

main :: IO ()
main = do
  h <- read <$> getLine
  m <- read <$> getLine
  putStrLn $ show $ Time (NInt h) (NInt m)


