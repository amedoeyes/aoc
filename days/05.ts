import aoc from "../aoc";

const input = aoc.input(5).split("\n\n");

const instructions = input[1]
	.split("\n")
	.map((instruction) => instruction.split(" ").filter(Number).map(Number));

function part01() {
	let crates = input[0]
		.split("\n")
		.map((row) => row.match(/.{1,4}/g)!.map((crate) => crate.trim()));
	let topCrates: string[] = [];

	for (const instruction of instructions) {
		for (let numOfCrates = 0; numOfCrates < instruction[0]; numOfCrates++) {
			for (let fromRow = 0; fromRow < crates.length - 1; fromRow++) {
				if (crates[fromRow][instruction[1] - 1]) {
					for (let toRow = 0; toRow < crates.length - 1; toRow++) {
						if (crates[0][instruction[2] - 1]) {
							crates.unshift(Array(crates[0].length).fill(""));
							crates[0][instruction[2] - 1] =
								crates[fromRow + 1][instruction[1] - 1];
							crates[fromRow + 1][instruction[1] - 1] = "";
							crates = crates.filter((row) =>
								row.some((crate) => crate)
							);
							break;
						}
						if (crates[toRow + 1][instruction[2] - 1]) {
							crates[toRow][instruction[2] - 1] =
								crates[fromRow][instruction[1] - 1];
							crates[fromRow][instruction[1] - 1] = "";
							crates = crates.filter((row) =>
								row.some((crate) => crate)
							);
							break;
						}
					}
					break;
				}
			}
		}
	}

	for (const row of crates) {
		for (let crate = 0; crate < row.length; crate++) {
			if (!topCrates[crate] && row[crate])
				topCrates[crate] = row[crate][1];
		}
	}

	return topCrates.join("");
}

function part02() {
	let crates = input[0]
		.split("\n")
		.map((row) => row.match(/.{1,4}/g)!.map((crate) => crate.trim()));
	let topCrates: string[] = [];

	for (const instruction of instructions) {
		for (
			let numOfCrates = instruction[0] - 1;
			numOfCrates >= 0;
			numOfCrates--
		) {
			for (let fromRow = 0; fromRow < crates.length - 1; fromRow++) {
				if (crates[fromRow][instruction[1] - 1]) {
					for (let toRow = 0; toRow < crates.length - 1; toRow++) {
						if (crates[0][instruction[2] - 1]) {
							crates.unshift(Array(crates[0].length).fill(""));
							crates[0][instruction[2] - 1] =
								crates[fromRow + numOfCrates + 1][
									instruction[1] - 1
								];
							crates[fromRow + numOfCrates + 1][
								instruction[1] - 1
							] = "";
							crates = crates.filter((row) =>
								row.some((crate) => crate)
							);
							break;
						}
						if (crates[toRow + 1][instruction[2] - 1]) {
							crates[toRow][instruction[2] - 1] =
								crates[fromRow + numOfCrates][
									instruction[1] - 1
								];
							crates[fromRow + numOfCrates][instruction[1] - 1] =
								"";
							crates = crates.filter((row) =>
								row.some((crate) => crate)
							);
							break;
						}
					}
					break;
				}
			}
		}
	}

	for (const row of crates) {
		for (let crate = 0; crate < row.length; crate++) {
			if (!topCrates[crate] && row[crate])
				topCrates[crate] = row[crate][1];
		}
	}

	return topCrates.join("");
}

aoc.execute(part01, part02);
