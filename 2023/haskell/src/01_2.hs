module Main where

import Data.Char (isDigit)
import Data.List (isPrefixOf, tails)
import Data.Maybe (listToMaybe, mapMaybe)

wordDigitMap :: [(String, Char)]
wordDigitMap = [("one", '1'), ("two", '2'), ("three", '3'), ("four", '4'), ("five", '5'), ("six", '6'), ("seven", '7'), ("eight", '8'), ("nine", '9')]

findDigit :: String -> Maybe Char
findDigit [] = Nothing
findDigit (c : cs)
  | isDigit c = Just c
  | otherwise = listToMaybe [d | (w, d) <- wordDigitMap, w `isPrefixOf` (c : cs)]

firstDigit :: String -> Maybe Char
firstDigit = listToMaybe . mapMaybe findDigit . tails

lastDigit :: String -> Maybe Char
lastDigit = listToMaybe . mapMaybe findDigit . reverse . tails

processLine :: String -> Int
processLine line =
  case (firstDigit line, lastDigit line) of
    (Just f, Just l) -> read [f, l]
    _ -> 0

main :: IO ()
main = do
  input <- readFile "input/01.txt"
  print $ sum $ map processLine $ lines input
