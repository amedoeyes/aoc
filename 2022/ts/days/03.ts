import aoc from "../aoc"

const rucksacks = aoc.input(3).split("\n")
const priority = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]

function part01() {
    let sum = 0
    
    rucksacks
    .map((rucksack:string) => [rucksack.slice(0, rucksack.length/2), rucksack.slice(rucksack.length/2)])
    .forEach((compartments:string[]) => {
    	 [...new Set(compartments[0].split(""))]
	 .forEach((item) => {
	    if (compartments[1].includes(item)) 
		sum += priority.indexOf(item) + 1
    	})
    })
    
    return sum
}

function part02() {
    let sum = 0

    rucksacks
    .map((_:string, index:number) => rucksacks
    .slice(index * 3, (index + 1) * 3))
    .slice(0, rucksacks.length / 3)
    .forEach((rucksack:string[]) => {
	[...new Set(rucksack[0].split(""))]
	.forEach((item) => {
	    if (rucksack[1].includes(item) && rucksack[2].includes(item)) 
		sum += priority.indexOf(item) + 1
	})
    })

    return sum
}

aoc.execute([part01, part02])
