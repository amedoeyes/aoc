import aoc from "../aoc";

const buffer = aoc.input(6).split("");
// const buffer = "mjqjpqmgbljsphdztnvjfqwrcgsmlb".split("");

function part01() {
	let sequence: string[] = [];

	for (let letter = 0; letter < buffer.length; letter++) {
		if (
			sequence.some((sequenceLetter) => sequenceLetter === buffer[letter])
		) {
			sequence = [];
			sequence.push(buffer[letter]);
		} else {
			sequence.push(buffer[letter]);
		}
		if (sequence.length === 4) return letter + 1;
	}
	return 0;
}

function part02() {
	let sequence: string[] = [];

	for (let letter = 0; letter < buffer.length; letter++) {
		if (
			sequence.some((sequenceLetter) => sequenceLetter === buffer[letter])
		) {
			sequence = sequence.slice(sequence.indexOf(buffer[letter]) + 1);
			sequence.push(buffer[letter]);
		} else {
			sequence.push(buffer[letter]);
		}

		if (sequence.length === 14) return letter + 1;
	}

	return 0;
}

aoc.execute(part01, part02);
