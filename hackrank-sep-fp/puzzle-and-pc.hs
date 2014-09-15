import qualified Data.List as L
import Control.Monad

type Loc = (Int, Int)
type Prob = (Int, Loc)

readInput :: IO (Prob)
readInput = do
	sz <- getLine
	ln <- getLine
	let num = map read $ L.words ln
	return (read sz, (head num, head $ tail num))

tile :: Int -> Loc -> Int
tile m (r,c)
	| r <= cell && c <= cell = 0
	| r <= cell && c > cell = 1
	| r > cell && c <= cell = 2
	| otherwise = 3
	where cell = 2^(m-1)

solve :: Int -> Loc -> Loc -> IO ()
solve m (x,y) (r,c)
	| m == 0 = return ()
	| m == 1 = putStrLn s
	| otherwise = do
		putStrLn s
		forM_ [0..3] (\i -> solve (m-1) (pos !! i) (subprob !! i))
	where
		quadrant = tile m (r,c)
		cell = 2^(m-1)
		holes = [ (a,b) | a<-[cell, cell+1], b<-[cell, cell+1] ]
		s = L.intercalate " " $ map (\(a,b)->(show $ x+a) ++ " " ++ (show $ y+b)) [ holes !! idx | idx<-[0..3], idx /= quadrant ]
		off = [ (a,b) | a<-[0, cell], b<-[0, cell] ]
		sub = [ if idx == quadrant then (r,c) else (holes !! idx) | idx<-[0..3] ]
		subprob = map (\(a,b)->(fst a - fst b, snd a - snd b)) $ zip sub off
		pos = map (\(a,b)->(x+a,y+b)) off

main :: IO ()
main = do
	input <- readInput
	solve (fst input) (0,0) (snd input)