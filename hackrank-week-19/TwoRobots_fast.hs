{-# LANGUAGE BangPatterns #-}

import Control.Applicative
import qualified Control.Monad as M
import qualified Data.Vector as V

data State = Full { src :: {-# UNPACK #-} !Int
                  , dst :: {-# UNPACK #-} !Int
                  }
           | Empty deriving (Eq, Show)

type States = V.Vector State

-- | Calculate the cost of @State@
cost :: State -- ^ State
     -> Int   -- ^ Cost to reach this state
cost Empty = 0
cost s     = abs $ src s - dst s

-- | Calculate the cost of moving from one state to another
move :: State -- ^ Source state
     -> State -- ^ Destination state
     -> Int   -- ^ Cost
move Empty q                     = cost q
move s1@(Full _ _) s2@(Full _ _) = cost s2 + abs (src s2 - dst s1)
move _ _                         = error "cannot move from Full to Empty"

solve :: IO ()
solve = do
  [_, n] <- map read . words <$> getLine
  query  <- V.replicateM n $ do
    [x, y] <- map read . words <$> getLine
    return (Full x y)
  putStrLn . show . calc n $ V.cons Empty query

-- | Dynamic programming
calc :: Int -> States -> Int
calc n states
  | n == 1    = iniVal
  | otherwise = calc' 2 n (V.singleton iniVal)
  where
    iniVal = cost (states V.! 1)
    move' :: Int -- ^ Start state index
          -> Int -- ^ End state index
          -> Int -- ^ Cost
    move' i j = move (states V.! i) (states V.! j)

    calc' :: Int          -- ^ Current index
          -> Int          -- ^ Total index
          -> V.Vector Int -- ^ Costs after prev state
          -> Int          -- ^ Min costs
    calc' i n dp
      | i > n     = V.minimum dp
      | otherwise = calc' (i+1) n (V.snoc lhs rhs)
      where
        inc = move' (i-1) i
        lhs = V.map (+ inc) dp
        rhs = minimum [ dp V.! j + move' j i | j <- [0..i-2] ]

-- | Main function
main :: IO ()
main = do
  t <- read <$> getLine
  M.replicateM_ t solve
