import Control.Monad

solve :: String -> Int
solve s = length s - (max (fst st) (snd st))
	where
	st = foldl move (0,0) s
	move (alen, blen) ch
		| ch == 'A' = (blen+1, blen)
		| otherwise = (alen, alen+1)

main :: IO ()
main = do
	t <- getLine
	forM_ [1..(read t)] $
		(\_ -> do
			s <- getLine 
			putStrLn $ show $ solve s)