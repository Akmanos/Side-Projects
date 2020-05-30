let values = [];
let w = 2;

function setup() {
    createCanvas(windowWidth, windowHeight);
    values = new Array(floor(random(250, width / 2)));
    for (i = 0; i < values.length; i++) {
        values[i] = (round(random(height)));
    }
    frameRate(3);
}
//show array changes
let clock = 1;

function draw() {
    background(0);
    values = mergeSort(values, clock);
    clock++;
    for (i = 0; i < values.length; i++) {
        noStroke();
        if (clock % 3 == 0) {
            fill('#F6743F');
        } else if (clock % 2 == 0) {
            fill('#3F9BF6');
        } else if (clock % 5 == 0) {
            fill('#CF5CF7');
        } else {
            fill(255);
        }
        rect(i * w, height - values[i], w, values[i]);
    }
    if (clock > 10) {
        noLoop();
    }
}

function mergeSort(arr, clk) {
    if (arr.length <= 1) {
        return arr;
    }
    clk--;
    if (clk < 1) {
        return arr;
    }
    let mid = round((arr.length / 2));
    let left = arr.slice(0, mid);
    let right = arr.slice(mid);
    return merge(mergeSort(left, clk), mergeSort(right, clk));
}

function merge(left, right) {
    sorted = [];
    while (left.length > 0 && right.length > 0) {
        if (left[0] <= right[0]) {
            sorted.push(left.shift());
        } else {
            sorted.push(right.shift());
        }
    }
    return sorted.concat(left, right);
}