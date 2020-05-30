//Nathaniel Taylor
//Quicksort with JS

//array of values to be sorted
let array = [];
//width of values
let w = 2;
//hold the state of the arrays
let states = [];

function setup() {
    createCanvas(windowWidth, windowHeight);
    array = new Array(floor(random(250, width / w)));
    for (let i = 0; i < array.length; i++) {
        array[i] = random(height);
        states[i] = -1;
    }
    //quicksort the array
    quickSort(array, 0, array.length - 1);
}

async function quickSort(arr, start, end) {
    //break case
    if (start >= end) {
        return;
    }
    //wait for recursive call
    let index = await rec(arr, start, end);
    states[index] = -1;

    await Promise.all([
        //split the array in half
        quickSort(arr, start, index - 1),
        quickSort(arr, index + 1, end)
    ]);
}

async function rec(arr, start, end) {
    for (let i = start; i < end; i++) {
        //set every value to in progress
        states[i] = 1;
    }

    let val = arr[end];
    let pivot = start;
    //change the state of the current value to being worked on
    states[pivot] = 0;
    for (let i = start; i < end; i++) {
        //if the current array val is less than the end
        if (arr[i] < val) {
            //swap the current index with pivot
            await swap(arr, i, pivot);
            //set current index to finished
            states[pivot] = -1;
            //move pivot to its ew location after swap
            pivot++;
            //set this new pivot to in progress
            states[pivot] = 0;
        }
        //if its greater move on
    }
    //when done sorting swap pivot with the last
    await swap(arr, pivot, end);

    for (let i = start; i < end; i++) {
        if (i != pivot) {
            states[i] = -1;
        }
    }

    return pivot;
}

function draw() {
    background(0);

    for (let i = 0; i < array.length; i++) {
        noStroke();
        if (states[i] == 0) {
            fill('#38e332');
        } else if (states[i] == 1) {
            fill('#c9c8c7');
        } else {
            fill(255);
        }
        //draw the array values at location x=i*w , y=height-array[i] with given width (w) and height(array[i])
        rect(i * w, height - array[i], w, array[i]);
    }
}

async function swap(arr, a, b) {
    //wait a bit
    await sleep(25);
    let temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}