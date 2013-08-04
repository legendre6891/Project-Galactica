
main = putStrLn . show $ solveHelper 100000000

solveHelper n = if good $ n+1000000000
                    then n+1000000000
                    else solveHelper $ n + 10

good n = let s = show $ n^2
         in '1' : evens ( drop 1 s ) == "1234567890"

evens xs = case drop 1 xs of
              (y:ys) -> y : evens ys
              [] -> []
