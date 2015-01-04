import Control.Applicative
import qualified Data.List as L
import qualified Data.Function as F

type Index = Int

-- | ax+b representation of line
data Line = Line { a :: Int
                 , b :: Int
                 } deriving (Eq, Show)

divide :: Int -> Int -> Double
divide = (/) `F.on` fromIntegral

instance Ord Line where
  compare (Line 0 b1) (Line 0 b2) = compare b1 b2
  compare (Line 0 _) (Line _ _) = LT
  compare (Line _ _) (Line 0 _) = GT
  compare (Line a1 b1) (Line a2 b2) = 
    compare (divide (-b1) a1) (divide (-b2) a2)

-- | left <= t < right max is index
data Range = Range { left  :: Int
                   , right :: Int
                   , index :: Index
                   } deriving (Eq, Show)

data Point = Point { x :: Double
                   , y :: Double
                   } deriving (Eq, Show)

-- | prepare sorted lines to scan
makeLines :: [(Int, Int)] -> [(Line, Index)]
makeLines ps = L.sortBy (compare `F.on` fst) $ zip ls [1..]
  where ls = map (\(x,y) -> Line x y) ps

cross :: Line -> Line -> Point
cross (Line a1 b1) (Line a2 b2) = Point x y
  where
    x = divide (b2 - b1) (a1 - a2)
    y = divide (a1*b2 - a2*b1) (a1 - a2)

envelope :: [Double] -> [(Line,Index)] -> [(Line,Index)] -> 

-- | scan left to right to find maximum envelope
findPoints :: [(Line, Index)] -> [Range] 
findPoints ln = foldl  ls
  where
    (zs,ls) = span (\(x,_) -> a x == 0) ln

query :: Int -> [Int] -> [Int] -> Int
query t inht rate = bld 
  where
    (_, bld) = L.maximum $ zip height [1..]
    height = map (\(x,y)-> x+t*y) $ zip inht rate

solve :: Int -> [Int] -> [Int] -> IO ()
solve 0 _ _ = return ()
solve q inht rate = do
  t <- read <$> getLine
  putStrLn $ show (query t inht rate) 
  solve (q-1) inht rate

main :: IO ()
main = do
  [_, q] <- map read . words <$> getLine
  inht <- map read . words <$> getLine
  rate <- map read . words <$> getLine
  solve q inht rate
