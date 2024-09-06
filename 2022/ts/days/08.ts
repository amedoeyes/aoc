import aoc from "../aoc";

const input = aoc
	.input(8)
	.trim()
	.split("\n")
	.map((row) => row.split(""));

class Tree {
	tree: string;
	top: string[];
	bottom: string[];
	left: string[];
	right: string[];

	constructor(rowIndex: number, columnIndex: number) {
		this.tree = input[rowIndex][columnIndex];
		this.top = input
			.filter((_, index) => index < rowIndex)
			.map((row) => row[columnIndex])
			.reverse();
		this.bottom = input
			.filter((_, index) => index > rowIndex)
			.map((row) => row[columnIndex]);
		this.left = input[rowIndex]
			.filter((_, index) => index < columnIndex)
			.reverse();
		this.right = input[rowIndex].filter((_, index) => index > columnIndex);
	}

	visible() {
		return (
			this.top.every((tree) => tree < this.tree) ||
			this.bottom.every((tree) => tree < this.tree) ||
			this.left.every((tree) => tree < this.tree) ||
			this.right.every((tree) => tree < this.tree)
		);
	}

	static analyseScene(tree: string, direction: string[]) {
		for (let index = 0; index < direction.length; index++) {
			if (direction[index] >= tree) {
				return direction.slice(0, index + 1);
			}
		}
		return direction;
	}

	scenicScore() {
		return (
			Tree.analyseScene(this.tree, this.top).length *
			Tree.analyseScene(this.tree, this.bottom).length *
			Tree.analyseScene(this.tree, this.left).length *
			Tree.analyseScene(this.tree, this.right).length
		);
	}
}

function part01() {
	let sum = 0;

	for (let rowIndex = 0; rowIndex < input.length; rowIndex++) {
		for (
			let columnIndex = 0;
			columnIndex < input[rowIndex].length;
			columnIndex++
		) {
			const tree = new Tree(rowIndex, columnIndex);

			if (tree.visible()) {
				sum++;
			}
		}
	}
	return sum;
}

function part02() {
	let scores: number[] = [];

	for (let rowIndex = 0; rowIndex < input.length; rowIndex++) {
		for (
			let columnIndex = 0;
			columnIndex < input[rowIndex].length;
			columnIndex++
		) {
			const tree = new Tree(rowIndex, columnIndex);
			scores.push(tree.scenicScore());
		}
	}
	return scores.reduce((sum, value) => (value > sum ? (sum = value) : sum));
}

aoc.execute(part01, part02);
