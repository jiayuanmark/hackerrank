import qualified Data.List as L
import Control.Monad

data Result = CENTRAL | LEFT | RIGHT | DEAD deriving (Show)

isPrime :: Integer -> Bool
isPrime x
	| x <= 1 = False
	| otherwise = isPrime' x 2
	where
		isPrime' x div
			| x < div * div = True
			| otherwise = (x `mod` div /= 0) && (isPrime' x (div+1))

check :: Integer -> Result
check x
	| zero || (not prime) = DEAD
	| left && right = CENTRAL
	| left = LEFT
	| right = RIGHT
	| otherwise = DEAD
	where
		prime = isPrime x
		zero = L.elem '0' (show x)
		left = all (isPrime . read) (init $ L.tails (show x))
		right = all (isPrime . read) (tail $ L.inits (show x))

main :: IO ()
main = do
	t <- getLine
	forM_ [1..(read t)] $ \_ ->
		do
			n <- getLine
			putStrLn $ show $ check (read n)