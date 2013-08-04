import Text.Printf
import Control.Exception
import System.CPUTime
 
one :: Int -> Int
one = length . show

two :: Double -> Int
two n = 1 + (floor ( (log n) / (log 10) ))

time :: IO t -> IO t
time a = do
    start <- getCPUTime
    v <- a
    end   <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10^12)
    printf "Computation time: %0.3f sec\n" (diff :: Double)
    return v
 
main = do
    x <- return $ two 10000
    return()
