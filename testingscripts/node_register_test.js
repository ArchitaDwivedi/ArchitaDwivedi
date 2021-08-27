// Objective:-
// This is a nodejs script which sends data (post) and registers a user if they do not already exist.
// Once registered, we get back user details and a newly generated token so the user can immediately 
// go and login if they want to.


// How to use:-
// First, start your server.
// Go to your terminal/cmd and into this project's testingscripts folder.
// Here we are using axios to make our request so make sure axios is installed. 
// If not use npm to install it or if you want to avoid installing it.
// Then just move this file to the frontend folder as axios is installed in there.
// Next Run this file:- "node node_register_test.js"



import axios from 'axios';


var data = JSON.stringify({
  "name": "Jillian Doe",
  "email": "jillian@example.com",
  "password": "123456"
});

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/users/',
  headers: { 
    'Content-Type': 'application/json'
  },
  data : data
};

axios(config)
.then(function (response) {
  console.log(JSON.stringify(response.data));
})
.catch(function (error) {
  console.log(error);
});