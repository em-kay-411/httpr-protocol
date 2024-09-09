const exec = require('child_process').exec;
const clientPath = __dirname + '/../build/client';

function httpr (endpoint, body){
    // httpr/127.0.0.1/function/

    let response;

    if(endpoint.split('/')[0] !== 'httpr'){
        console.log('Error');
        return;
    }

    const host = endpoint.split('/')[1];
    const functionCall = endpoint.split('/')[2];

    const request = {functionCall, body};

    // console.log(JSON.stringify(request));
    // console.log('client path', clientPath);
    // console.log(`${clientPath} "${host}" "${JSON.stringify(request)}"`)
    exec(`${clientPath} "${host}" "${JSON.stringify(request)}"`, (error, stderr, stdout) => {
        response = stdout;
    })

    return response;
}

module.exports = httpr;