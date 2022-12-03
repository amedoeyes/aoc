import fs from "fs";
import path from "path";

function addLeadingZero(number: number) {
	const strNum = number.toString();
	const strNumWithZero = strNum.padStart(2, "0");

	return strNum.length === 1 ? strNumWithZero : strNum;
}

function execute(functions: (() => any)[]) {
	console.time("time");
	functions.forEach((func, index) =>
		console.log(`part${addLeadingZero(index + 1)}:`, func())
	);
	console.timeEnd("time");
}

function input(file: number) {
	return fs.readFileSync(
		path.resolve(__dirname, `inputs/${addLeadingZero(file)}.txt`),
		"utf-8"
	);
}

export default { execute, input };
