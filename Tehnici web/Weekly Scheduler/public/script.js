Days = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
DaysLower = ["sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"]
Months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "Octomber", "November", "December"]

n =  new Date();
const day = n.getDay(); //zi a saptamanii
const y = n.getFullYear(); //an
const m = n.getMonth(); //luna
const d = n.getDate();//zi a lunii
var cnt = 0;

document.getElementById("time").innerHTML = Days[day] + ", " + d + " " + Months[m] + " "+  y;

var header = document.getElementsByTagName("header")[0];

addButton = document.getElementById("addButton");
//updateButton = document.getElementById("updateButton")

inputHour = document.getElementById ("formHour")
inputDay = document.getElementById ("days");
inputActivity = document.getElementById ("formActivity");

var dayDivs = {};
for(let i = 0; i < DaysLower.length; i++)
    dayDivs[DaysLower[i]] = document.getElementById (DaysLower[i]);

var zileStar = {}
for (let i = 0; i < 7; i++)
    zileStar[DaysLower[i]] = Days[i];

///////////////////////////////////           functii                    ///////////////////////////////////////////////////////

function resetForm() {
    inputHour.value = '';
    inputActivity.value = '';
}

function createActivity(activity){
    //creare elemente DOM
    cnt++;

    var container = document.createElement("div");
    container.className = 'dayGrid'
    container.id = 'div' + cnt;
    dayDivs[activity.day].appendChild(container);

    var hourDiv = document.createElement("div");
    hourDiv.className = 'ore';
    hourDiv.innerHTML = activity.hour;
    container.appendChild(hourDiv);

    var activityDiv = document.createElement("div");
    activityDiv.innerHTML = activity.activity;
    container.appendChild(activityDiv);
    
    var buttonsDiv = document.createElement("div");
    let editButton = document.createElement('button')
    editButton.addEventListener('click', function () {
            editActivity(container.id, activity)
    });
    editButton.innerHTML = '<i class="far fa-edit"></i>';

    deleteButton = document.createElement('button')
    deleteButton.addEventListener('click', function () {
            deleteActivity(activity._id)
     });
    deleteButton.innerHTML = '<i class="fas fa-trash-alt"></i>';
    
    starButton = document.createElement('button')

    if (activity.stare == 1)
        starButton.innerHTML = '<i class="fas fa-star" style="color:#FF7B9C;"></i>';
    else 
        starButton.innerHTML = '<i class="far fa-star"></i>';
        
    starButton.addEventListener('click', function () {
        updateStar(activity);
    });

    buttonsDiv.appendChild(editButton);
    buttonsDiv.appendChild(deleteButton);
    buttonsDiv.appendChild(starButton);
    container.appendChild(buttonsDiv);
}

function appendToDOM(activities){
    //stergere elemente DOM
    for(let i = 0; i < DaysLower.length; i++)
        while(dayDivs[DaysLower[i]].firstChild)
            dayDivs[DaysLower[i]].removeChild(dayDivs[DaysLower[i]].firstChild);
    
    for(let i = 0; i < activities.length; i++)
        createActivity(activities[i]);
}

function appendStar(activities){

    let Container = document.getElementById('important')
    while(Container.firstChild)
            Container.removeChild(Container.firstChild);

    for (let j=0; j<7; j++)
        for(let i = 0; i < activities.length; i++)
            if (activities[i].stare == 1 && activities[i].day == DaysLower[j])
            {
                var container = document.createElement("div");
                container.className = "gridForImportant";
                var daySpan = document.createElement("span");
                daySpan.innerHTML = zileStar[activities[i].day] + " ";
                container.appendChild(daySpan);

                var hourSpan = document.createElement("span");
                hourSpan.innerHTML = activities[i].hour + " ";
                container.appendChild(hourSpan);

                var activitySpan = document.createElement("span");
                activitySpan.innerHTML = activities[i].activity;
                activitySpan.className = "textImportant"
                container.appendChild(activitySpan);

                Container.appendChild(container);
            }
        
}


function addActivity(){
    const postObject = {
        stare: 0,
        hour: inputHour.value,
        day: inputDay.value,
        activity: inputActivity.value
    }
    postActivity(postObject);
}

function cancelUpdate(id){
    
    var divInputContainer = document.getElementById(id);
    divInputContainer.removeChild(document.getElementById('container' + id));
}


function editActivity( id, activity) {

    var divInputContainer = document.getElementById(id);

    var inputContainer = document.createElement("div");
    inputContainer.id = 'container' + id;
    inputContainer.className = 'edit';
    
    var dayInput = document.createElement("select");
    dayInput.className = 'editInput';
    dayInput.innerHTML = '<option value="monday">Monday</option><option value="tuesday">Tuesday</option><option value="wednesday">Wednesday</option><option value="thursday">Thursday</option><option value="friday">Friday</option><option value="saturday">Saturday</option><option value="sunday">Sunday</option>';
    dayInput.value = activity.day;
    dayInput.id = 'day' + id;

    var hourInput = document.createElement("input");
    hourInput.className = 'editInput';
    hourInput.type = "time"
    hourInput.autocomplete = 'off'
    hourInput.placeholder = 'Hour'
    hourInput.value = activity.hour;
    hourInput.id = 'hour' + id;

    var textInput = document.createElement("input");
    textInput.className = 'editInput';
    textInput.autocomplete = 'off'
    textInput.placeholder = 'Activity'
    textInput.value = activity.activity;
    textInput.id = 'activity' + id;

    var saveButton = document.createElement('button')
    saveButton.addEventListener('click', function () {
            updateActivity(id, activity) 
    });
    
    saveButton.innerHTML = '<i class="far fa-save"></i>';
    saveButton.id = 'save' + id;

    var cancelButton = document.createElement('button')
    cancelButton.addEventListener('click', function () {
            cancelUpdate(id) 
    });
    
    cancelButton.innerHTML = '<i class="far fa-window-close"></i>';
    cancelButton.id = 'cancel' + id;

    inputContainer.appendChild(dayInput)
    inputContainer.appendChild(hourInput)
    inputContainer.appendChild(textInput)
    inputContainer.appendChild(saveButton)
    inputContainer.appendChild(cancelButton)

    divInputContainer.appendChild(inputContainer);
}


//////////////////////////////////////////////////              AJAX                  /////////////////////////////////////////

function getActivities(){
    //AJAX GET
    fetch('/activities')
    .then(function (response) {
        response.json().then(function (activities) {
            appendToDOM(activities);
            appendStar(activities);
        });
    });
}

function postActivity(postObject){
    //AJAX POST
    fetch('/activities', {
        method: 'post',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(postObject)
    }).then(function () {
        getActivities();
        resetForm();
    }).catch(function(err) {
        console.log('Fetch Error:-S', err);
    });
}

function deleteActivity(id) {
    //AJAX DELETE
    fetch('/activities', {
        method: 'delete',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          _id: id
        })
      })
        .then(function() {
            getActivities();
    })

}

function updateActivity(containerId, activity){

    //AJAX PUT
    fetch('/activities', {
        method: 'put',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            ID: activity._id,
            stare: activity.stare,
            hour: document.getElementById('hour' + containerId).value,
            day: document.getElementById('day' + containerId).value,
            activity: document.getElementById('activity' + containerId).value
        })
      })
        .then(res => {
            getActivities();
        })
}

function updateStar(activity){

    fetch('/activities', {
        method: 'put',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            ID: activity._id,
            stare: 1 - activity.stare, 
            hour: activity.hour,
            day: activity.day,
            activity:activity.activity
        })
      })
        .then(res => {
            getActivities();
        })
    
}

////////////////////////////////                 login                       //////////////////////////////////////////////

function logOut(){
    localStorage.removeItem('name');
    document.getElementById("title").innerHTML = "Your Weekly Schedule"
    utilizatorNelogat()
}

function makePersonal(){
    localStorage.name = document.getElementById("Name").value;
    document.getElementById("title").innerHTML = document.getElementById("Name").value + "'s Weekly Schedule"
    utilizatorLogat()
}
function utilizatorLogat(){
    // editare element DOM
    header.innerHTML = "";
    var p = document.createElement("span")
    p.className = "Name";
    p.innerText = localStorage.name;
    var d = document.createElement("span")
    d.innerHTML = '<button type="button" id="logOutButton" class="logOut">Log out</button>'
    d.className = 'name'
    header.appendChild(p)
    header.appendChild(d)
    document.getElementById("logOutButton").addEventListener('click', logOut)

}

function utilizatorNelogat() {

    header.innerHTML = "";
    var labelForName = document.createElement("div");
    labelForName.innerHTML = "<label for='Name' class='name'> Tell us your name here </label>";
    labelForName.className = 'Name';

    let divPentruInputsiButon =  document.createElement("span");
    divPentruInputsiButon.className = "addName";

    var inputName = document.createElement("span");
    inputName.innerHTML = '<input type="text" name="name" id="Name" autocomplete="off" class="inputNume"></input>';

    var sendButton = document.createElement("span")
    sendButton.innerHTML = '<button type="button" id="nameButton"><i class="far fa-check-circle"></i></button>'
    
    header.appendChild(labelForName)
    divPentruInputsiButon.appendChild(inputName)
    divPentruInputsiButon.appendChild(sendButton)
    header.appendChild(divPentruInputsiButon)
    sendButton.addEventListener('click', makePersonal);
}

if (localStorage.name)
{
    document.getElementById("title").innerText = localStorage.name + "'s Weekly Schedule"
    utilizatorLogat();
}
else 
{
    utilizatorNelogat();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//eveniment declansat de mouse

addButton.addEventListener('click', addActivity);

getActivities();