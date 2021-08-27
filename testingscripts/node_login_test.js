// Objective:-
// This is a nodejs script to test and see if we can get back a response from
// our server after we have made a post request with some data.
// In this case, we want to get back details about a particular use after having
// sent that user's email and password in the post request's payload.

// How to use:-
// First, start your server.
// Go to your terminal/cmd and into this project's testingscripts folder.
// Here we are using axios to make our request so make sure axios is installed. 
// If not use npm to install it or if you want to avoid installing it.
// Then just move this file to the frontend folder as axios is installed in there.
// Next Run this file:- "node node_login_test.js"


import axios from 'axios';
var data = JSON.stringify({
  "email": "john@example.com",
  "password": "123456"
});

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/users/login',
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
