import Control.Applicative
import qualified Data.List as L
import qualified Data.Function as F

-- | ax+b representation of line
data Line = Line { a :: Int
				 , b :: Int
				 }
		deriving (Eq, Show)

instance Ord Line where
	compare (Line 0 b1) (Line 0 b2) = compare b1 b2
	compare (Line 0 _) (Line _ _) = LT
	compare (Line _ _) (Line 0 _) = GT
	compare (Line a1 b1) (Line a2 b2) = 
		let calc = (/) `F.on` fromIntegral
		in compare (calc (-b1) a1) (calc (-b2) a2)

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
