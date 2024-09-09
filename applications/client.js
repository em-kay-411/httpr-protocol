const httpr = require('../httpr/httpr.js');

const main = () => {
    const endpoint = 'httpr/127.0.0.1/add';
    const body = {a : 1, b : 2}
    console.log(httpr(endpoint, body));
}

main();