import aoc from "../aoc";

const elves = aoc
	.input(1)
	.split("\n\n")
	.map((elf) =>
		elf.split("\n").reduce((sum, value) => Number(sum) + Number(value), 0)
	)
	.sort((a, b) => Number(b) - Number(a));

function part01() {
	return elves[0];
}

function part02() {
	return elves.slice(0, 3).reduce((sum, value) => sum + value);
}

aoc.execute([part01, part02]);
