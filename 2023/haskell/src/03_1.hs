module Main where

import Data.Char (isDigit)

type Board = [[Char]]

type Coord = (Int, Int)

inBounds :: Board -> Coord -> Bool
inBounds board (r, c) = r >= 0 && r < length board && c >= 0 && c < length (head board)

getAdjCoords :: Board -> Coord -> [Coord]
getAdjCoords board (r, c) = [(r + r', c + c') | (r', c') <- [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)], inBounds board (r + r', c + c')]

isAdjToSym :: Board -> Coord -> Bool
isAdjToSym board (r, c) = any (\(r', c') -> isSym (board !! r' !! c')) (getAdjCoords board (r, c))
  where
    isSym char = not (isDigit char) && char /= '.'

getNumCoords :: Board -> Coord -> [Coord]
getNumCoords board (r, c)
  | inBounds board (r, c) && isDigit (board !! r !! c) = (r, c) : getNumCoords board (r, c + 1)
  | otherwise = []

assembleNum :: Board -> [Coord] -> Int
assembleNum board = read . concatMap (\(r, c) -> [board !! r !! c])

processRow :: Board -> Coord -> [Int]
processRow board (r, c)
  | c >= length (head board) = []
  | isDigit (board !! r !! c) && any (isAdjToSym board) (getNumCoords board (r, c)) =
      let num = getNumCoords board (r, c)
       in assembleNum board num : processRow board (r, c + length num)
  | otherwise = processRow board (r, c + 1)

processBoard :: Board -> Int
processBoard board = sum $ concat [processRow board (r, 0) | r <- [0 .. length board - 1]]

main :: IO ()
main = do
  input <- readFile "input/03.txt"
  print $ processBoard $ lines input
