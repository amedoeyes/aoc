module Main where

import Data.Char (isDigit)
import Data.List (nub)
import Data.Maybe (fromJust)

type Board = [[Char]]

type Coord = (Int, Int)

inBounds :: Board -> Coord -> Bool
inBounds board (r, c) = r >= 0 && r < length board && c >= 0 && c < length (head board)

getAdjCoords :: Board -> Coord -> [Coord]
getAdjCoords board (r, c) = [(r + r', c + c') | (r', c') <- [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)], inBounds board (r + r', c + c')]

getNumStartCoord :: Board -> Coord -> Maybe Coord
getNumStartCoord board (r, c)
  | inBounds board (r, c) && isDigit (board !! r !! c) && inBounds board (r, c - 1) && isDigit (board !! r !! (c - 1)) = getNumStartCoord board (r, c - 1)
  | inBounds board (r, c) && not (isDigit (board !! r !! c)) = Nothing
  | otherwise = Just (r, c)

getNumCoords :: Board -> Coord -> [Coord]
getNumCoords board (r, c)
  | inBounds board (r, c) && isDigit (board !! r !! c) = (r, c) : getNumCoords board (r, c + 1)
  | otherwise = []

assembleNum :: Board -> [Coord] -> Int
assembleNum board = read . concatMap (\(r, c) -> [board !! r !! c])

processRow :: Board -> Coord -> [Int]
processRow board (r, c)
  | c >= length (head board) = []
  | board !! r !! c == '*' = do
      let digitsCoords = filter (\(r', c') -> isDigit (board !! r' !! c')) (getAdjCoords board (r, c))
      let numsCoords = nub $ map (\(r', c') -> getNumCoords board (fromJust (getNumStartCoord board (r', c')))) digitsCoords
      let result = if length numsCoords == 2 then product [assembleNum board num | num <- numsCoords] else 0
      result : processRow board (r, c + 1)
  | otherwise = processRow board (r, c + 1)

processBoard :: Board -> Int
processBoard board = sum $ concat $ [processRow board (r, 0) | r <- [0 .. length board - 1]]

main :: IO ()
main = do
  input <- readFile "input/03.txt"
  print $ processBoard $ lines input
