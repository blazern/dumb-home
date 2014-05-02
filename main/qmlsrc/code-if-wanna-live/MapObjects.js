var mapObjects = new Array()

function get(index) {
    return mapObjects[index];
}

function add(item) {
    mapObjects.push(item)
}

function clear() {
    mapObjects = [];
}

function size() {
    return mapObjects.length;
}
