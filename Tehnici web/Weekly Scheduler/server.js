//server backend

const express = require('express')
const bodyParser = require('body-parser')
const app = express()
app.use(express.static('public'))
app.use(bodyParser.json())


const MongoClient = require('mongodb').MongoClient;
const uri = "connection link";

MongoClient.connect(uri, {
  useUnifiedTopology: true
    }, (err, client) => {
  if (err) return console.error(err)

  console.log('Connected to Database');

  const db = client.db('weekly-scheduler');
  const activitiesCollection = db.collection('activities');


  app.use(bodyParser.urlencoded({ extended: true }))

  app.listen(3000, function () {
    console.log('listening on 3000')
  })
  //READ
  app.get('/activities', function (req, res) {
      let mySort = { hour : 1};
      const cursor = activitiesCollection.find().sort(mySort).toArray()
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
    let ObjectId = require('mongodb').ObjectID
    let id = new ObjectId(req.body._id);
    activitiesCollection.deleteOne(
      { "_id": id }
    )
      .then(result => {
        res.redirect("")
      })
      .catch(error => console.error(error))
  })
  //UPDATE
  app.put('/activities', (req, res) => {
    let ObjectId = require('mongodb').ObjectID
    let id = new ObjectId(req.body.ID);
    activitiesCollection.findOneAndUpdate(
      { "_id": id },
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
