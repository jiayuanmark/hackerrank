import qualified Data.List as L

solve :: Int -> [Int] -> String -> String
solve val num s | val `seq` num `seq` s `seq` False = undefined 
solve val [] s
  | val `mod` 101 == 0 = s
  | otherwise = ""
solve val num@(n:ns) s
  | val `mod` 101 == 0 = (s ++ concat (replicate (length num) " *"))
  | length t1 /= 0 = t1
  | length t2 /= 0 = t2
  | otherwise = t3
  where
    t1 = solve (val+n) ns (s ++ " +")
    t2 = solve (val-n) ns (s ++ " -")
    t3 = solve (val*n) ns (s ++ " *") 

main = do
  n <- getLine
  input <- getLine
  let lst = L.words input
  let num = map read lst
  let symb = L.words $ solve (head num) (tail num) ""
  putStrLn $ (head lst) ++ (L.intercalate "" $ map (\(x,y) -> x ++ y) $ zip symb (tail lst))