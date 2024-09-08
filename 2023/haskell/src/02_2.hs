module Main where

import Data.List.Split (splitOn)

parseGame :: String -> (Int, [[(String, Int)]])
parseGame s = case splitOn ": " s of
  [game, sets] -> (read (splitOn " " game !! 1) :: Int, map (map parseCube . splitOn ", ") (splitOn "; " sets))
  [game] -> (read (splitOn " " game !! 1) :: Int, [])
  _ -> (0, [])
  where
    parseCube s' = case splitOn " " s' of
      [n, c] -> (c, read n :: Int)
      _ -> ("", 0)

findMaxCubes :: [[(String, Int)]] -> [(String, Int)]
findMaxCubes =
  foldr findMax [("red", 0), ("green", 0), ("blue", 0)] . concat
  where
    findMax (n, c) cubes = case cubes of
      [r, g, b] -> case n of
        "red" -> [(fst r, max (snd r) c), g, b]
        "green" -> [r, (fst g, max (snd g) c), b]
        "blue" -> [r, g, (fst b, max (snd b) c)]
        _ -> [r, g, b]
      _ -> cubes

calculatePower :: [(String, Int)] -> Int
calculatePower = foldr ((*) . snd) 1

main :: IO ()
main = do
  input <- readFile "input/02.txt"
  print $ sum $ map ((calculatePower . findMaxCubes . snd) . parseGame) (lines input)
