

prefixCompress :: String -> String -> Int -> Int
prefixCompress x [] s = s
prefixCompress [] y s = s
prefixCompress (x:xs) (y:ys) s
	| x == y = prefixCompress xs ys (s+1)
	| otherwise = s

main :: IO ()
main = do
	x <- getLine
	y <- getLine
	let pos = prefixCompress x y 0
	let lx = length x
	let ly = length y
	putStrLn $ (show pos) ++ " " ++ (take pos x)
	putStrLn $ (show (lx - pos)) ++ " " ++ (drop pos x)
	putStrLn $ (show (ly - pos)) ++ " " ++ (drop pos y)