Months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "Octomber", "November", "December"]
//////////////////////////////////////////                  Login / register                 ////////////////////////////////////////////////////
// Get the modal
var modal = document.getElementById("myModal");
var logButton = document.getElementById("LoginButton");
var registerButton = document.getElementById("RegisterButton");
//get IntroDiv
var chooseOp = document.getElementById("Intro");
//get LoginDiv
var logDiv = document.getElementById("LoginFields");
//get RegisterDiv
var regDiv = document.getElementById("RegisterFields");

// buttons for confirmation
var logConf = document.getElementById("sendLogInfo");
var regConf = document.getElementById("sendRegInfo");

function addLoginFields(){
    chooseOp.style.display = "none";
    logDiv.style.display = "block";
}

function addRegFields(){
    chooseOp.style.display = "none";
    regDiv.style.display = "block";
}

////////////// Register
var userNameInput = document.getElementById("formName");
var userBirthDayInput = document.getElementById("formDate");
var userEmailInput = document.getElementById("formRegEmail");
var userPsw1Input = document.getElementById("formRegPassword");
var userPsw2Input = document.getElementById("formRegPassword2");

backRegButton = document.getElementById("backReg");
backRegButton.onclick = function(){
    regDiv.style.display = "none";
    userNameInput.value = "";
    userEmailInput.value = "";
    userPsw1Input.value = "";
    userPsw2Input.value = "";
    userBirthDayInput.value = "";
    chooseOp.style.display = "block";
}

function addUser(){
    let userName = userNameInput.value;
    let userBirthDay = userBirthDayInput.value;
    let userEmail = userEmailInput.value;
    userPsw1 = userPsw1Input.value;
    userPsw2 = userPsw2Input.value;
    
    if (!userName || !userBirthDay ||!userEmail || !userPsw1 || !userPsw2) {
       alert("Please fill all the fileds!")
       return;
    }
    if (!checkDate(userBirthDay)){
        alert("Birth date does not respect format or is invalid.")
        return;
    }

    if ( userEmail.indexOf('@') == -1){
        alert("Please insert a valid email address!");
        return;
    }
    if (userPsw1.length < 6){
        alert("Password must be at least 6 characters long.");
        return;
    }
    if (userPsw1 !== userPsw2){
        alert("Passwords do not match.");
        return;
    }
    let register_time = new Date(Date.now());
    const postObject = {
        name: userName,
        birthDay: userBirthDay,
        email: userEmail,
        psw: userPsw1,
        IP: 'no login',
        date: register_time,
        visits: 0
    }

    fetch('/users', {
        method: 'post',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(postObject)
    }).then(function (response) {
        
        response.json().then( function(result){
            if (result.message == "succes"){
                chooseOp.style.display = "block";
                regDiv.style.display = "none";
                alert("Registration succesful!");
                //clears register input
                userNameInput.value = "";
                userEmailInput.value = "";
                userPsw1Input.value = "";
                userPsw2Input.value = "";
                userBirthDayInput.value = "";
            }
            
            else
                alert("Email already exits in database.")
        })

    }).catch(function(err) {
        console.log('Fetch Error:-S', err);
    });
}

///////////////////////////     Login
backLogButton = document.getElementById("backLog");
backLogButton.onclick = function(){
    logDiv.style.display = "none";
    document.getElementById("formEmail").value = "";
    document.getElementById("formPassword").value ="";
    chooseOp.style.display = "block";
}
logConf.onclick = function(){
    let emailLog = document.getElementById("formEmail").value;
    let pswLog = document.getElementById("formPassword").value;

    fetch("https://api.ipify.org/?format=json") // cerinta 3.8
    .then( function (response) { 
        response.json().then(function (data) {
            const postObject = {
                email: emailLog,
                psw: pswLog,
                IP: data.ip
            }
            
            fetch('/login', {
                method: 'post',
                headers: {
                    "Content-type": "application/json"
                },
                body: JSON.stringify(postObject)
            }).then(function (response) {
                response.json().then( function(result){
                    if (result.message == "succes"){
                        modal.style.display = "none"
                        localStorage.name = result.name;
                        localStorage.userId = result.userId;
                        localStorage.WSUserBirth = result.birthDay;
                        let date = new Date(result.time);
                        if (result.IP == 'no login')
                            alert("Hi, " +  result.name + "! You logged in today for the first time.");
                        else 
                            alert("Hi, " +  result.name + "! Last time you logged in from this IP: " + result.IP + " on " + date.getDate()+ " " + Months[date.getMonth()] + " " + date.getFullYear() + " at " + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + ". You visited Weekly Scheduler " + result.visits + " times.");
                        utilizatorLogat();
                        getActivities();
                        // clears login input
                        document.getElementById("formEmail").value = "";
                        document.getElementById("formPassword").value = "";
                    }
                    else
                        alert(result.message);
                })
            }).catch(function(err) {
                console.log('Fetch Error:-S', err);
            });
            
        })
    });


   }
    logButton.addEventListener('click', addLoginFields);
    registerButton.addEventListener('click', addRegFields);
    regConf.addEventListener('click', addUser);

function utilizatorNelogat(){
    modal.style.display = "block";
    chooseOp.style.display = "block";
    logDiv.style.display = "none";
    regDiv.style.display = "none";

}
 
//////////////////////////////////                       functionalitate site                       ////////////////////////////////////////////

Days = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
DaysLower = ["sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"]

n =  new Date();
const day = n.getDay(); //zi a saptamanii
const y = n.getFullYear(); //an
const m = n.getMonth(); //luna
const d = n.getDate(); //zi a lunii
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
        activity: inputActivity.value,
        userId: localStorage.userId
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
    if (localStorage.name){
    fetch('/activities/' + localStorage.userId)
    .then(function (response) {
        response.json().then(function (activities) {
            appendToDOM(activities);
            appendStar(activities);
        });
    });
    }
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
          _id: id,
          userId: localStorage.userId
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
            activity: document.getElementById('activity' + containerId).value,
            userId: localStorage.userId
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
            activity: activity.activity,
            userId: localStorage.userId
        })
      })
        .then(res => {
            getActivities();
        })
    
}

////////////////////////////////                 verifica daca utilizatorul este logat                  //////////////////////////////////////////////



function logOut(){
    localStorage.removeItem('name');
    header.innerHTML = "";
    utilizatorNelogat();
}

function utilizatorLogat(){
    // editare element DOM
        header.innerHTML = "";
        var p = document.createElement("span")
        p.className = "Name";
        p.innerText = localStorage.name;
        var d = document.createElement("span")
        d.innerHTML = '<button type="button" id="logOutButton" class = "headerButtons">Log out</button>'
        d.className = 'name'
        var bAge = document.createElement("span");
        bAge.innerHTML = '<button type="button" id="getAge" class = "headerButtons"> Get your current age!</button>'
        bAge.className = 'name'
        bAge.id = 'AgeSpanButton'
        header.appendChild(p)
        header.appendChild(d)
        header.appendChild(bAge)
        document.getElementById("getAge").addEventListener('click', getAge);
        document.getElementById("logOutButton").addEventListener('click', logOut)
}

if (localStorage.name)
{
    //document.getElementById("title").innerText = localStorage.name + "'s Weekly Schedule"
    utilizatorLogat();
}
else 
{
    utilizatorNelogat();
}

////////////////////////////////////                Cerinte Examen               //////////////////////////////////////////////

// 2.4 
var footer = document.getElementsByTagName("footer")[0];
function timpPetrecutpePagina()
{
    if (localStorage["timeWS"])
        localStorage["timeWS"]++;
    else
        localStorage["timeWS"] = 1;
    let sec = localStorage["timeWS"] % 60;
    let min = (localStorage["timeWS"]  - sec ) / 60;
    footer.innerText = "You spent " + min + " minutes " + sec + " seconds on Your Weekly Schedule.";
}
setInterval(timpPetrecutpePagina, 1000);

// 2.1
const NumberOFDays = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
function Bisect(a){
    if (a % 4 == 0 && ( a % 100 != 0 || a % 400 == 0))
        return true;
    return false;
}
function checkDate(data)
{
    if (data.length != 10)
        return false;
    if (data[2] != '#' || data[5]!= '#')
        return false;
    let z = data[1] - '0' + 10 * (data[0] - '0');
    let l = (data[4] - '0') + 10 * (data[3] - '0');
    let a = (data[9] - '0') + (data[8] - '0') *10 + (data[7] - '0') * 100 + (data[6] - '0') * 1000;
    
    if ( l < 0 || l > 12 )
        return false;
    
    if ( l == 2 && Bisect(a)) ///februarie an bisect
    {
        if ( z <= 0 || z > 29)
            return false;
    }
    else
    {
        if ( z < 1 || z > NumberOFDays[l-1])
            return false;
    }            
    return true;
}
var itv;
function hideAge(){
    if (document.getElementById("ageDiv"))
        header.removeChild(document.getElementById("ageDiv"));
    header.removeChild(document.getElementById("stop"));
    bAge = document.createElement("span");
    bAge.innerHTML = '<button type="button" id="getAge" class = "headerButtons">Get your current age!</button>'
    bAge.className = 'name'
    bAge.id = 'AgeSpanButton'
    header.appendChild(bAge)
    bAge.addEventListener('click', getAge);
    clearInterval(itv);
}
function getAge()
{
    if (document.getElementById("ageDiv"))
        header.removeChild(document.getElementById("ageDiv"));
    var divAge = document.createElement("div");
    divAge.id = "ageDiv";
    header.appendChild(divAge);
    showAge()
    itv = setInterval(showAge, 1000);
    header.removeChild(document.getElementById("AgeSpanButton"));
    var stop = document.createElement("span");
    stop.innerHTML = '<button type="button" id="hideAge" class = "headerButtons">Hide age</button>'
    stop.id = "stop";
    header.appendChild(stop);
    document.getElementById("hideAge").addEventListener('click', hideAge);
}

function showAge()
{
    
    let currDate = new Date();
    data = localStorage.WSUserBirth;
    let min = currDate.getMinutes();
    let sec = currDate.getSeconds();
    let hour = currDate.getHours() ;
    let Bday = data[1] - '0' + 10 * (data[0] - '0');
    let Bmonth = (data[4] - '0') + 10 * (data[3] - '0');
    let Byear = (data[9] - '0') + (data[8] - '0') *10 + (data[7] - '0') * 100 + (data[6] - '0') * 1000;
    var years, months, days;
    if ( Bmonth > m || (Bmonth == m && Bday > d)){
        years = y - Byear - 1;
        months = 12 - (Bmonth - (m + 1));
        if (d < Bday)
            months-=1;
    }
    else{
        years = y - n - 1;
        months = m + 1 - Bmonth;
    }
    if ( d >= Bday)
        days = d - Bday;
    else{
        days = d + NumberOFDays[Bmonth - 1] - Bday;
        if (Bmonth == 2 && Bisect(Byear))
            days+=1;
    }
    if(document.getElementById("ageDiv"))
        document.getElementById("ageDiv").innerText = years + ' years ' + months + ' months ' + days + ' days ' + hour + ' hours ' + min + ' minutes ' + sec + 'seconds';
    else
        clearInterval(itv);
}
//2.3
function titleAnimation()
{
    var title = document.getElementsByTagName('h1')[0];
    var splitText = ["Y", "o" ,"u" , "r", " ", "W", "e", "e", "k", "l", "y", " ", " S", "c", "h", "e", "d", "u", "l", "e"];
    var newTitle = [" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "];
    var i = 0;
    var mid = splitText.length / 2;
    function Animate()
    {
        if ( i > mid )
        {
            if (splitText.length % 2)
                newTitle[i] = splitText[i];
            clearInterval(titleIntv);
        }
        else{
            newTitle[i] = splitText[i];
            newTitle[splitText.length - i - 1] = splitText[splitText.length - i - 1];
        }
        let intermediar = "";
        for (let j = 0; j < splitText.length; j++)
             intermediar += newTitle[j];
        title.innerText = intermediar;
        i++;
    }
    var titleIntv = setInterval(Animate, 100);
}
//3.13
function activityWatcher(){
 
    var secondsSinceLastActivity = 0;

    var maxInactivity = 5; //seconds
 
    setInterval(function(){
        secondsSinceLastActivity++;
        if(secondsSinceLastActivity > maxInactivity){
            //create element div
            if(document.getElementById("inactivity"))
            document.getElementById("inactivity").innerText = "You have been inactive for " + secondsSinceLastActivity + " seconds";
            else{
            var div = document.createElement("div");
            div.id = "inactivity";
            div.innerText = "You have been inactive for " + secondsSinceLastActivity + " seconds";
            document.getElementsByTagName('body')[0].appendChild(div);
            }
        }
    }, 1000);
 
    function activity(){
        secondsSinceLastActivity = 0;
        if(document.getElementById("inactivity"))
            document.getElementsByTagName('body')[0].removeChild(document.getElementById("inactivity"));
    }
    var activityEvents = [
        'mousedown', 'mousemove', 'keydown',
        'scroll', 'touchstart'
    ];
 
    activityEvents.forEach(function(eventName) {
        document.addEventListener(eventName, activity, true);
    })
}
 
activityWatcher();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

addButton.addEventListener('click', addActivity);
titleAnimation();
getActivities();

