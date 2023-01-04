import aoc from "../aoc"

const pairs = aoc.input(4).trim().split("\n").map((pair:string) => pair.split(",").map((pair:string) => pair.split("-").map(Number)))

function part01() {
    let contained = 0

    pairs.forEach((pair:number[][]) => {	
	if(pair[0][0] >= pair[1][0] && pair[0][1] <= pair[1][1] || pair[1][0] >= pair[0][0] && pair[1][1] <= pair[0][1])
	    contained++
    })
	
    
    return contained
}

function part02() {
    let overlap = 0

    pairs.forEach((pair:number[][]) => {
	if(pair[0][0] >= pair[1][0] && pair[0][0] <= pair[1][1] || pair[0][1] <= pair[1][1] && pair[0][1] >= pair[1][0] || pair[1][0] >= pair[0][0] && pair[1][0] <= pair[0][1] || pair[1][1] <= pair[0][1] && pair[1][1] >= pair[0][0])
	    overlap++
    })

    return overlap
}

aoc.execute([part01, part02])
