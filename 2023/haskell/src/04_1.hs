module Main where

import Data.List.Split (splitOn)

type Card = (Int, [Int], [Int])

parseCard :: String -> Card
parseCard s =
  let s' = splitOn ":" s
      cardId = read $ drop 4 (head s')
      nums = map (map read . filter (not . null) . splitOn " ") $ splitOn " | " (last s')
   in (cardId, head nums, last nums)

calculateScore :: Card -> Int
calculateScore (_, a, b) =
  let matches = length $ filter (`elem` a) b
   in if matches > 0 then 2 ^ (matches - 1) else 0

main :: IO ()
main = do
  input <- readFile "input/04.txt"
  print $ sum $ map (calculateScore . parseCard) (lines input)
