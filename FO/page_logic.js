let E_value = 0.0;
let E_step = 1e-10;
let E_max = 2e-9;
let E_min = 0.0;

let B_value = 0.0;
let B_step = 1e-11;
let B_max = 1e-10;
let B_min = -1e-10;

function incrementValue(group) {
  if (group === 'E') {
    E_value = Math.min(E_value + E_step, E_max);
    document.getElementById("E_value").innerText = E_value;
    document.getElementById("Eslider").value = E_value;
  } else if (group === 'B') {
    B_value = Math.min(B_value + B_step, B_max);
    document.getElementById("B_value").innerText = B_value;
    document.getElementById("Bslider").value = B_value;
  }
}

function decrementValue(group) {
  if (group === 'E') {
    E_value = Math.max(E_value - E_step, E_min);
    document.getElementById("E_value").innerText = E_value;
    document.getElementById("Eslider").value = E_value;
  } else if (group === 'B') {
    B_value = Math.max(B_value - B_step, B_min);
    document.getElementById("B_value").innerText = B_value;
    document.getElementById("Bslider").value = B_value;
  }
}

function resetValue(group) {
  if (group === 'E') {
    E_value = 0;
    document.getElementById("E_value").innerText = E_value;
    document.getElementById("Eslider").value = E_value;
  } else if (group === 'B') {
    B_value = 0;
    document.getElementById("B_value").innerText = B_value;
    document.getElementById("Bslider").value = B_value;
  }
}
