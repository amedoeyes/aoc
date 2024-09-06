import aoc from "../aoc";

const strategy = aoc
	.input(2)
	.split("\n")
	.map((round) => round.split(" "));

function part01() {
	let score = 0;

	strategy.forEach((round) => {
		switch (round[1]) {
			case "X":
				score += 1;
				switch (round[0]) {
					case "C":
						score += 6;
						break;
					case "A":
						score += 3;
						break;
				}
				break;

			case "Y":
				score += 2;
				switch (round[0]) {
					case "A":
						score += 6;
						break;
					case "B":
						score += 3;
						break;
				}
				break;

			case "Z":
				score += 3;
				switch (round[0]) {
					case "B":
						score += 6;
						break;
					case "C":
						score += 3;
						break;
				}
				break;
		}
	});

	return score;
}

function part02() {
	let score = 0;

	strategy.forEach((round) => {
		switch (round[1]) {
			case "X":
				switch (round[0]) {
					case "A":
						score += 3;
						break;
					case "B":
						score += 1;
						break;
					case "C":
						score += 2;
						break;
				}
				break;

			case "Y":
				switch (round[0]) {
					case "A":
						score += 4;
						break;
					case "B":
						score += 5;
						break;
					case "C":
						score += 6;
						break;
				}
				break;

			case "Z":
				switch (round[0]) {
					case "A":
						score += 8;
						break;
					case "B":
						score += 9;
						break;
					case "C":
						score += 7;
						break;
				}
				break;
		}
	});

	return score;
}

aoc.execute([part01, part02]);
