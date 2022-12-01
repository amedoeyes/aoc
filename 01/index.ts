import fs from "fs";
import path from "path";

const elves = fs
	.readFileSync(path.resolve(__dirname, "input.txt"), "utf8")
	.split("\n\n")
	.map((value) =>
		value.split("\n").reduce((sum, value) => Number(sum) + Number(value), 0)
	)
	.sort((a, b) => Number(b) - Number(a));

const sumOfTopThree = elves.slice(0, 3).reduce((sum, value) => sum + value);

console.log("part01", elves[0]);
console.log("part02", sumOfTopThree);
