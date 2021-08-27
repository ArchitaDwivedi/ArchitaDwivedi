// Objective:-
// This is a nodejs script to GET all products

// How to use:-
// First, start your server.
// Go to your terminal/cmd and into this project's testingscripts folder.
// Here we are using axios to make our request so make sure axios is installed. 
// If not use npm to install it or if you want to avoid installing it.
// Then just move this file to the frontend folder as axios is installed in there.
// Next Run this file:- "node node_fetchall_test.js"


import axios from 'axios';

var config = {
  method: 'get',
  url: 'http://localhost:5000/api/products/',
  headers: { }
};

axios(config)
.then(function (response) {
  console.log(JSON.stringify(response.data));
})
.catch(function (error) {
  console.log(error);
});
