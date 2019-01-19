// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const {app} = require('electron').remote;
const fs = require('fs');


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

function setVoterOrAdmin ( voterOrAdmin ) {
    global.clientSettings.role = voterOrAdmin;
    fs.writeFileSync ( app.getAppPath('userData') + "/clientSettings.json", JSON.stringify ( global.clientSettings ), { encoding : 'utf8' } );
}

function showUserIndex() {
    document.getElementsByClassName('js-role-selection')[0].style.display = 'none';
    if (global.clientSettings.role == 'Admin') {
        document.getElementsByClassName('js-admin-index')[0].style.display = 'flex';
    } else {
        document.getElementsByClassName('js-employee-index')[0].style.display = 'flex';
    }
}

document.getElementsByClassName('js-role-button-employee')[0].addEventListener('click', function(){
    setVoterOrAdmin("Employee");
    showUserIndex();
});

document.getElementsByClassName('js-role-button-admin')[0].addEventListener('click', function(){
    setVoterOrAdmin("Admin");
    showUserIndex();
});