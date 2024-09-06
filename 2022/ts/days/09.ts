import aoc from "../aoc";

const input = `R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2`
	.split("\n")
	.map((motion) => motion.split(" "));

class Bridge {
	#grid = [["H"]];
	#covered: { elements: string[]; position: [number, number] } = {
		elements: ["T", "s"],
		position: [0, 0],
	};
	#tailPositions: [number, number][] = [];

	get getGrid() {
		return this.#grid;
	}

	#headPosition(): [number, number] {
		for (let row = 0; row < this.#grid.length; row++) {
			for (let column = 0; column < this.#grid[row].length; column++) {
				if (this.#grid[row][column] === "H") return [row, column];
			}
		}

		return [0, 0];
	}

	#tailPosition(): [number, number] {
		for (let row = 0; row < this.#grid.length; row++) {
			for (let column = 0; column < this.#grid[row].length; column++) {
				if (this.#grid[row][column] === "T") return [row, column];
			}
		}

		if (this.#covered.elements.some((element) => element === "T"))
			return this.#covered.position;

		return [0, 0];
	}

	#pushToTailPositions() {
		if (!this.#tailPositions.includes(this.#tailPosition()))
			this.#tailPositions.push(this.#tailPosition());
	}

	#cover(direction: string, position: [number, number]) {
		switch (direction) {
			case "U":
				if (
					position[0] != 0 &&
					this.#grid[position[0] - 1][position[1]]
				) {
					this.#covered.elements.push(
						this.#grid[position[0] - 1][position[1]]
					);

					this.#covered.position = [position[0] - 1, position[1]];
				}
				break;
			case "D":
				if (
					position[0] != this.#grid.length - 1 &&
					this.#grid[position[0] + 1][position[1]]
				) {
					this.#covered.elements.push(
						this.#grid[position[0] + 1][position[1]]
					);

					this.#covered.position = [position[0] + 1, position[1]];
				}
				break;
			case "L":
				if (
					position[0] != 0 &&
					this.#grid[position[0]][position[1] - 1]
				) {
					this.#covered.elements.push(
						this.#grid[position[0]][position[1] - 1]
					);

					this.#covered.position = [position[0], position[1] - 1];
				}
				break;
			case "R":
				if (
					position[0] != this.#grid[0].length - 1 &&
					this.#grid[position[0]][position[1] + 1]
				) {
					this.#covered.elements.push(
						this.#grid[position[0]][position[1] + 1]
					);

					this.#covered.position = [position[0], position[1] + 1];
				}
				break;
		}
	}

	#uncover(position: [number, number]) {
		if (
			this.#covered.position.join() === position.join() &&
			this.#covered.elements.length > 0
		) {
			this.#grid[position[0]][position[1]] = this.#covered.elements[0];
			this.#covered.elements = this.#covered.elements.slice(1);
		}
	}

	moveHead(direction: string, times: number) {
		for (let index = 0; index < times; index++) {
			this.#cover(direction, this.#headPosition());

			let row = this.#headPosition()[0];
			let column = this.#headPosition()[1];

			switch (direction) {
				case "U":
					if (this.#headPosition()[0] === 0) {
						this.#grid.unshift(
							Array(this.#grid[0].length).fill("")
						);

						row++;
						this.#covered.position[0]++;
					}

					this.#grid[row - 1][column] = "H";
					break;

				case "D":
					if (this.#headPosition()[0] === this.#grid.length - 1)
						this.#grid.push(Array(this.#grid[0].length).fill(""));

					this.#grid[row + 1][column] = "H";
					break;

				case "L":
					if (this.#headPosition()[1] === 0) {
						this.#grid.map((row) => row.unshift(""));

						column++;
						this.#covered.position[1]++;
					}

					this.#grid[row][column - 1] = "H";
					break;

				case "R":
					if (this.#headPosition()[1] === this.#grid[0].length - 1)
						this.#grid.map((row) => row.push(""));

					this.#grid[row][column + 1] = "H";
					break;
			}

			this.#grid[row][column] = "";
			this.#uncover([row, column]);
			this.#moveTail(direction);
		}
	}

	#isHeadAroundTail() {
		return (
			this.#tailPosition().join() === this.#headPosition().join() ||
			this.#tailPosition().join() ===
				[this.#headPosition()[0], this.#headPosition()[1] - 1].join() ||
			this.#tailPosition().join() ===
				[this.#headPosition()[0], this.#headPosition()[1] + 1].join() ||
			this.#tailPosition().join() ===
				[this.#headPosition()[0] - 1, this.#headPosition()[1]].join() ||
			this.#tailPosition().join() ===
				[this.#headPosition()[0] + 1, this.#headPosition()[1]].join() ||
			this.#tailPosition().join() ===
				[
					this.#headPosition()[0] - 1,
					this.#headPosition()[1] - 1,
				].join() ||
			this.#tailPosition().join() ===
				[
					this.#headPosition()[0] + 1,
					this.#headPosition()[1] - 1,
				].join() ||
			this.#tailPosition().join() ===
				[
					this.#headPosition()[0] - 1,
					this.#headPosition()[1] + 1,
				].join() ||
			this.#tailPosition().join() ===
				[
					this.#headPosition()[0] + 1,
					this.#headPosition()[1] + 1,
				].join()
		);
	}

	#moveTail(direction: string) {
		if (!this.#isHeadAroundTail()) {
			this.#cover(direction, this.#tailPosition());

			let row = this.#tailPosition()[0];
			let column = this.#tailPosition()[1];

			switch (direction) {
				case "U":
					this.#grid[this.#headPosition()[0] + 1][
						this.#headPosition()[1]
					] = "T";
					break;
				case "D":
					this.#grid[this.#headPosition()[0] - 1][
						this.#headPosition()[1]
					] = "T";
					break;
				case "L":
					this.#grid[this.#headPosition()[0]][
						this.#headPosition()[1] + 1
					] = "T";
					break;
				case "R":
					this.#grid[this.#headPosition()[0]][
						this.#headPosition()[1] - 1
					] = "T";
					break;
			}

			this.#grid[row][column] = "";
			this.#uncover([row, column]);
			this.#pushToTailPositions();
		}
	}
}

function part01() {
	const bridge = new Bridge();

	for (const motion of input) {
		bridge.moveHead(motion[0], Number(motion[1]));
	}

	return 0;
}

aoc.execute(part01);
