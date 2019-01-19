// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const {app} = require('electron').remote;
const fs = require('fs');
const networking = require('./networking.js');

console.log(app.getAppPath('userData'));

try {
    global.clientSettings  = JSON.parse ( 
        fs.readFileSync ( app.getAppPath('userData') + "/clientSettings.json", { encoding : 'utf8' } )
    );
    console.log('FILE FOUND');
}
catch(e){
    console.log('FILE NOT FOUND');
    global.clientSettings = {};
}

if (global.clientSettings.role){
    showUserIndex()
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

    //SHOW CURRENT VOTE
    if (global.clientSettings.vote){
        console.log("THERE IS A VOTE")
        var initVoteButtons = document.getElementsByClassName('js-vote-button');
        for (let initVoteButton of initVoteButtons) {
            if(global.clientSettings.vote.change_request == initVoteButton.dataset.vote){
                initVoteButton.classList.add("selected-vote");
            }
        }
        if (global.clientSettings.vote.change_request && global.clientSettings.vote.change_request != 0){
            document.getElementsByClassName('voted')[0].style.transform = 'scale(1) rotate(35deg)';
        }
    }
}

function createUser() {
    const userParams = { user: { role : global.clientSettings.role } }
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

var voteButtons = document.getElementsByClassName('js-vote-button');
for (let voteButton of voteButtons) {
    voteButton.addEventListener('click', function(){
        for (let element of voteButtons) {
            element.classList.remove("selected-vote");
        }

        const userVote = { vote : { change_request : parseInt(voteButton.dataset.vote) } };

        var currentVote = global.clientSettings.vote || { change_request : undefined }
        
        if(currentVote.change_request != voteButton.dataset.vote){
            console.log("NEW VOTE");
            console.log(global.clientSettings.currentUserId);
            document.getElementsByClassName('voted')[0].style.transform = 'scale(0) rotate(0deg)';
            updateClientSettings(userVote);
            voteButton.classList.add("selected-vote");
            networking.post({
                path: '/votes/vote',
                body: userVote,
                headers: {
                    'Authorization': global.clientSettings.currentUserId
                },
                callback: function (body) {
                    document.getElementsByClassName('voted')[0].style.transform = 'scale(1) rotate(35deg)';
                }
            });
        } else {
            console.log("DELETE VOTE");
            console.log(global.clientSettings.currentUserId);
            const defaultVote = { vote : { change_request : 0 } } 
            updateClientSettings(defaultVote);
            networking.post({
                path: '/votes/vote',
                body: defaultVote,
                headers: {
                    'Authorization': global.clientSettings.currentUserId
                },
                callback: function (body) {
                    document.getElementsByClassName('voted')[0].style.transform = 'scale(0) rotate(0deg)';
                }
            });
        }
        
        
    });
}