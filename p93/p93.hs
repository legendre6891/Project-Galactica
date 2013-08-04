
ops = [(+),(-),(*),(/)]
opPerms = [ [a,b,c] | a <- ops, b <- ops, c <- ops ]

genValues :: [a] -> [a -> a] -> a
genValues vals ops = [ (ops !! 2) (vals !! 3) ( (ops !! 1) (vals !! 2) ( (ops !! 0) (vals !! 1) (vals !! 0))) ]
