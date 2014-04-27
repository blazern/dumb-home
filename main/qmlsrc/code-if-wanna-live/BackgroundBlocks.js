var buttons = new Array()

function get(index) {
    return buttons[index];
}

function add(item) {
    buttons.push(item)
}

function clear() {
    buttons = [];
}

function size() {
    return buttons.length;
}
