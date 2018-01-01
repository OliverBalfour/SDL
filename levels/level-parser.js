
let data = '';

process.stdin.resume();
process.stdin.setEncoding('utf8');

process.stdin.on('data', chunk => data += chunk);
process.stdin.on('end', () => {
    data = JSON.parse(data);
    console.log(`${data.width} ${data.height}`);
    console.log(`${data.tilesets[0].image} ${data.tilesets[0].tilewidth} ${data.tilesets[0].columns}`);
    console.log(data.layers[0].data);
});
