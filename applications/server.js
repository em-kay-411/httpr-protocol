const add = (a, b) => {
    return Number(a + b);
}

const subtract = (a, b) => {
    return Number(a - b);
}

const convertToValidJsonString = (str) => {
    //string : "string : "

    str = str.replace(/([a-zA-Z0-9_]+)\s*:/g, '"$1":');
    str = str.replace(/:\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*(,|\})/g, ':"$1"$2');

    // console.log('string', str);

    return str;
}

const main = () => {
    // console.log(process.argv[2]);

    let response = {data : '', status : ''};

    const requestArgument = convertToValidJsonString(process.argv[2]);
    const request = JSON.parse(requestArgument);

    const functionCall = request.functionCall;

    // GET, POST, PUT

    if(functionCall === 'add'){
        const ans = add(Number(request.body.a), Number(request.body.b));
        // console.log(ans);
        response.data = ans;
    }
    else if(functionCall === 'subtract'){
        const ans = subtract(Number(request.body.a), Number(request.body.b));
        // console.log(ans);
        response.data = ans;
    }
    else{
        response.data = null;
        response.status = "FAILURE";
        return;
    }

    response.status = "SUCCESS";

    console.log(JSON.stringify(response));
}

main();