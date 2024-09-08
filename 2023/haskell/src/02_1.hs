module Main where

import Data.List.Split (splitOn)

maxCubes :: [(String, Int)]
maxCubes = [("red", 12), ("green", 13), ("blue", 14)]

isGamePossible :: (Int, [[(String, Int)]]) -> Bool
isGamePossible (_, sets) = foldr ((&&) . foldr ((&&) . isCubePossible) True) True sets
  where
    isCubePossible (n, c) = case lookup n maxCubes of
      Just m -> c <= m
      _ -> False

parseGame :: String -> (Int, [[(String, Int)]])
parseGame s = case splitOn ": " s of
  [game, sets] -> (read (splitOn " " game !! 1) :: Int, map (map parseCube . splitOn ", ") (splitOn "; " sets))
  [game] -> (read (splitOn " " game !! 1) :: Int, [])
  _ -> (0, [])
  where
    parseCube s' = case splitOn " " s' of
      [n, c] -> (c, read n :: Int)
      _ -> ("", 0)

main :: IO ()
main = do
  input <- readFile "input/02.txt"
  print $ sum $ map fst $ filter isGamePossible $ map parseGame (lines input)
