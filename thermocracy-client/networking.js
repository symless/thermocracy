const request = require('request');
//const API_URL = "https://ba8b42bb-fc9b-4701-8e8d-40431531d355.mock.pstmn.io"
const API_URL = "http://192.168.1.17:8080"

const get = function({ path, callback, ...options }) {
    request({
        method: 'GET',
        url: API_URL + path,
        json: true,
        ...options
    }, 
    (e, r, b) => handleResponse(e, r, b, callback)
    );
}

const post = function({ path, body, callback, ...options }) {
    request({
        method: 'POST',
        url: API_URL + path,
        json: true,
        body,
        ...options
    },
    (e, r, b) => handleResponse(e, r, b, callback)
    );
}

function handleResponse(error, response, body, callback) {
    console.log('error:', error); // Print the error if one occurred
    console.log('statusCode:', response && response.statusCode); // Print the response status code if a response was received
    console.log('body:', body); // Print the HTML for the Google homepage.
    if (error == undefined) {
        callback(body);
    }
}

module.exports = {
    get: get,
    post: post
}