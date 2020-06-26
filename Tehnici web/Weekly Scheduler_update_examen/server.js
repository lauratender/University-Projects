//server backend

const express = require('express')
const bodyParser = require('body-parser')
const bcrypt = require('bcrypt');
const app = express()
app.use(express.static('public'))
app.use(bodyParser.json())


const MongoClient = require('mongodb').MongoClient;
const uri = "mongodb+srv://user:psw@cluster0-aaozr.mongodb.net/test?retryWrites=true&w=majority";

MongoClient.connect(uri, {
  useUnifiedTopology: true
    }, (err, client) => {
  if (err) return console.error(err)

  console.log('Connected to Database');

  const db = client.db('weekly-scheduler');
  const activitiesCollection = db.collection('activities');
  const usersCollection = db.collection('users');

  app.use(bodyParser.urlencoded({ extended: true }))

  app.listen(3000, function () {
    console.log('listening on 3000')
  })

  const ObjectId = require('mongodb').ObjectID;

  // User

  app.post('/users', (req, res) => {

    usersCollection.findOne({"email": req.body.email})
    .then(result => {
        if(result) {
          let state = { "message": "User already exits"}
          res.send(state);
        }     
        else {
          bcrypt.genSalt(10, function(err, salt) {
            bcrypt.hash(req.body.psw, salt, function(err, hash) {
              if (err) throw err;
              req.body.psw = hash;
              usersCollection.insertOne(req.body)
              .then( result => {
                let state = {"message": "succes"}; 
                res.status(200).send(state);
              })
              .catch(error => console.error(error))
            });
          });
        }
    })
    .catch(err => console.error('Failed findOne in Register'));
  })

  app.post('/login', (req, res) => {

    usersCollection.findOne({"email": req.body.email})
    .then(result => {
        if(result) {
          bcrypt.compare(req.body.psw, result.psw, function(err, match) {
            if (match == true){
              userId = new ObjectId(result._id);
              let login_time = new Date(Date.now());
              let state = {"message": "succes", "name": result.name, "userId": result._id, "birthDay": result.birthDay, 'IP': result.IP, 'time': result.date, 'visits': result.visits};
              usersCollection.findOneAndUpdate(
                { "_id": userId },
                {
                  $set: {
                    IP: req.body.IP,
                    date: login_time,
                    visits: result.visits + 1
                  }
                },
                {
                  upsert: true
                }
              )
                .then(result => { 
                  res.status(200).send(state);
                })
                .catch(error => console.error(error))
            }
            else{
              //console.log('Passwords do not match');
              let state = { "message": "Passwords do not match"}
              res.send(state);
            }
          });
        }     
        else {
         //console.log("User not found.");
         let state = { "message": "User not found."}
         res.send(state);
        }}
    )
    .catch(err => console.error('Failed findOne in Login'));
    
})

  // Activities
  //READ
  app.get('/activities/:id', function (req, res) {
      let mySort = { hour : 1};
      const cursor = activitiesCollection.find({"userId": req.params.id}).sort(mySort).toArray()
      .then(results => {
        res.send(results);
      })
      .catch(error => console.error(error))
  })

  //CREATE
  app.post('/activities', (req, res) => {

    activitiesCollection.insertOne(req.body)
      .then(result => {
        res.status(200);
        res.redirect("/");
      })
      .catch(error => console.error(error))
  })

  ///DELETE
  app.delete('/activities', (req, res) => {
    let activityId = new ObjectId(req.body._id);
    //let userId = new ObjectId(req.body.userId);
    activitiesCollection.deleteOne(
      { "_id": activityId, "userId":  req.body.userId}
    )
      .then(result => {
        res.redirect("")
      })
      .catch(error => console.error(error))
  })

  //UPDATE
  app.put('/activities', (req, res) => {
  
    let id = new ObjectId(req.body.ID);
    activitiesCollection.findOneAndUpdate(
      { "_id": id, "userId": req.body.userId },
      {
        $set: {
          stare: req.body.stare,
          hour: req.body.hour,
          day: req.body.day,
          activity: req.body.activity
        }
      },
      {
        upsert: true
      }
    )
      .then(result => { 
        res.redirect("")
      })
      .catch(error => console.error(error))
  })
})
