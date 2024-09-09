module Main where

import Data.List.Split (splitOn)
import Data.Map qualified as Map
import Data.Maybe (fromJust)

type Card = (Int, [Int], [Int])

type CardMap = Map.Map Int Int

parseCard :: String -> Card
parseCard s =
  let parts = splitOn ":" s
      cardId = read $ drop 4 (head parts)
      nums = map (map read . filter (not . null) . splitOn " ") $ splitOn " | " (last parts)
   in (cardId, head nums, last nums)

calculateScore :: Card -> Int
calculateScore (_, a, b) = length $ filter (`elem` a) b

distributeCopies :: Int -> Int -> CardMap -> CardMap
distributeCopies i s m
  | s == 0 = m
  | otherwise =
      let m' = Map.insertWith (+) i 1 m
       in distributeCopies (i + 1) (s - 1) m'

distributeCopiesLoop :: Int -> Int -> Int -> CardMap -> CardMap
distributeCopiesLoop n i s m
  | n == 0 = m
  | otherwise = distributeCopiesLoop (n - 1) i s (distributeCopies i s m)

processCard :: Card -> CardMap -> CardMap
processCard (i, a, b) m =
  let score = calculateScore (i, a, b)
      copies = fromJust (Map.lookup i m)
   in distributeCopiesLoop copies (i + 1) score m

processCards :: [Card] -> CardMap -> Int
processCards cs m = sum $ foldl (flip processCard) m cs

main :: IO ()
main = do
  input <- readFile "input/04.txt"
  let cards = map parseCard (lines input)
      cardsMap = Map.fromList [(i, 1) | (i, _, _) <- cards]
      result = processCards cards cardsMap
  print result
