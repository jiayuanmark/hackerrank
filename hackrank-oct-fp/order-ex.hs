import qualified Data.List as L

-- | subarray array index maxValEnd (maxSoFar, maxStart) left right
subarray :: [Int] -> Int -> Int -> (Int,Int) -> Int -> Int -> (Int, (Int, Int))
subarray (x:xs) idx maxend (maxval,st) lft rht
  | update <= 0 = subarray xs (idx+1) 0 (maxval,st) (idx+1) rht
  | update > maxval = subarray xs (idx+1) update (update,lft) lft idx
  | otherwise = subarray xs (idx+1) update (maxval,st) lft rht
  where update = maxend + x

subarray [] _ _ (maxval,st) _ rht = (maxval,(st,rht))


solve :: Int -> [Int]-> IO ()
solve k array
  | (maxval == 0 || k == 0) = return ()
  | otherwise =
    do
      putStrLn $ show maxval
      solve (k-1) $ (take (l-1) array) ++ (drop r array)  
  where (maxval, (l, r)) = subarray array 1 0 (0,0) 1 1


main :: IO()
main = do
  sz <- getLine
  let k = read $ last (L.words sz)
  payload <- getLine
  solve k $ map read (L.words payload)