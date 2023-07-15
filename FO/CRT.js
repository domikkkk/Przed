let E = 0; // V/m
let B = 3e-11;
const dt = 0.01;
let es = [];
let width = 1200;
let height = 800;
let canvas;
let updateCanvas;
let change_E;
let actual_E;
let change_B;
let actual_B;
const pi = Math.pi;

class electron {
    constructor(posX, posY, R=NaN) {
        this.pos = {x: posX, y: posY}; // pozycja na canvasie
        this.v = 0; // prędkość [m/s]
        this.alpha = 0; // kąt odchylenia od osi x
        this.r = R || 10;
        this.q = -1.602e-19;  // ładunek [C]
        this.m = 9.1e-31;  // [kg]
        this.execution = 0; // jak wyjdzie poza ekran to zrobić rach ciach ciach
    }

    draw() {
        strokeWeight(1);
        fill(0, 150, 200);
        circle(this.pos.x, this.pos.y, this.r);
    }

    update(E=0, B=0) {
        let vX = this.v * cos(this.alpha);
        let vY = this.v * sin(this.alpha);
        this.pos.x += vX * dt;
        if(this.pos.x > width - 10 || this.pos.x < 0){
            this.execution = 1;
        }
        this.pos.y -= vY *dt;
        if(this.pos.y < 0 || this.pos.y > height){
            this.execution = 1;
        }
        if(this.pos.x < 2/3 * width - 15) {
            let ax = this.q * E / this.m;
            vX += ax * dt;
        }
        else if (this.pos.x < 2/3 * width -5) {
            let ay = this.q * vX * B / this.m;
            vY -= ay * dt;
        }

        // wyznaczanie w którą stronę elektron jest skierowany (tzn się porusza) i obliczenie wartości v
        if (vX > 0) {
            this.alpha = atan(vY / vX);
        }
        else if (vX < 0) {
            this.alpha = atan(vY / vX) + pi;
        }
        else {
            this.alpha = vY>0?pi/2: vY<0?-pi/2:0;
        }
        this.v = (vX**2 + vY**2)**(1/2);
    }
}


function setup() {
    canvas = createCanvas(width, height);
    canvas.parent('js');
    updateCanvas = document.getElementById('update_Canvas');
    updateCanvas.addEventListener('click', update_Canvas);
    change_E = document.getElementById('Eslider');
    change_E.addEventListener("change", update_E);
    actual_E = document.getElementById("E_value");
    actual_E.textContent = 0;
    change_B = document.getElementById('Bslider');
    change_B.addEventListener("change", update_B);
    actual_B = document.getElementById("B_value");
    actual_B.textContent = 0;
}

function update_E() {
    E = -change_E.value;
    actual_E.textContent = E;
}

function update_B() {
    B = change_B.value;
    actual_B.textContent = B;
}

function update_Canvas() {
    es.length = 0;
    width = document.getElementById("width-input").value;
    height = document.getElementById("height-input").value;
    canvas = createCanvas(width, height);
    canvas.parent('js');
}


function update_all() {
    for (let e of es) {
        e.update(E=E, B=B);
        e.draw();
        if(e.execution == 1){
            let i = es.findIndex(q => q.pos === e.pos);
            es.splice(i, 1);
        }
    }
}


function mousePressed() {
    if (mouseX < 2 * width / 3 && mouseY < 3/5 * height && mouseY > 2/5 * height){
        es.push(new electron(mouseX, mouseY));
    }
}


function draw_tube() {
    let thickness = 5;
    strokeWeight(thickness);
    stroke((0, 0, 0));
    line(0, 2/5*height, 2/3*width, 2/5*height);
    line(0, 3/5*height, 2/3*width, 3/5*height);
}


function draw_magnetic_field() {
    let ringColor = color(255, 0, 0, 100); // Czerwony kolor z przezroczystością (wartości RGBA)
    fill(ringColor);
    strokeWeight(0);
    let R1 = 30;
    let R2 = 2/3 * R1;
    let R3 = 1/3 * R1;
    let imax = Math.floor(1/5 * height / R1);
    let x = width * 2/3 - 10;
    let y = height * 2/5 + (1/5*height - imax * R1) / 2 + R1/2;
    for (let i = 0; i< imax; i++){
        circle(x, y + i*R1, R1);
        fill(220);
        circle(x, y + i*R1, R2);
        fill(ringColor);
        circle(x, y + i*R1, R3);
    }
}


function draw() {
    background(220);
    draw_magnetic_field();
    update_all();
    draw_tube();
    console.log(es.length);
}
