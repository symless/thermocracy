// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const {app} = require('electron').remote;
const fs = require('fs');
const request = require('request');
const networking = require('./networking.js');
const API_URL = "https://ba8b42bb-fc9b-4701-8e8d-40431531d355.mock.pstmn.io"

console.log(app.getAppPath('userData'));

try {
    global.clientSettings  = JSON.parse ( 
        fs.readFileSync ( app.getAppPath('userData') + "/clientSettings.json", { encoding : 'utf8' } )
    );
    console.log('FILE FOUND');
    showUserIndex()
}
catch(e){
    console.log('FILE NOT FOUND');
    global.clientSettings = {};
}

function updateClientSettings( props ) {
    global.clientSettings =  { ...global.clientSettings, ...props }
    fs.writeFileSync ( app.getAppPath('userData') + "/clientSettings.json", JSON.stringify ( global.clientSettings ), { encoding : 'utf8' } );

    const { currentTemperature } = props
    if (currentTemperature != undefined) {
        document.getElementsByClassName('js-temperature-display')[0].innerHTML = currentTemperature + '<span>°</span>'
    }
}

function setVoterOrAdmin ( voterOrAdmin ) {
    updateClientSettings({ role: voterOrAdmin })
    createUser();
}

function fetchHomeScreenData() {
    networking.get({
        path: '/temperature/current',
        headers: {
            'Authorization': global.clientSettings.currentUserId
        },
        callback: function (body) {
            updateClientSettings({ currentTemperature: body.current_temperature })
        }
    });
}

function showUserIndex() {
    document.getElementsByClassName('js-role-selection')[0].style.display = 'none';
    fetchHomeScreenData();
    if (global.clientSettings.role == 'Admin') {
        document.getElementsByClassName('js-admin-index')[0].style.display = 'flex';
    } else {
        document.getElementsByClassName('js-employee-index')[0].style.display = 'flex';
    }
}

function createUser() {
    const userParams = { role : global.clientSettings.role }
    networking.post({
        path: '/user',
        body: userParams,
        callback: function (body) {
            const { user } = body;
            updateClientSettings({ currentUserId: user.id })
        }
    });
}

document.getElementsByClassName('js-role-button-employee')[0].addEventListener('click', function(){
    setVoterOrAdmin("Employee");
    showUserIndex();
});

document.getElementsByClassName('js-role-button-admin')[0].addEventListener('click', function(){
    setVoterOrAdmin("Admin");
    showUserIndex();
});