// Objective:-
// This is a nodejs script which tries to get the user's information. We
// send a bearer token along with us since the route is protected.

// How to use:-
// First, start your server.
// Go to your terminal/cmd and into this project's testingscripts folder.
// Here we are using axios to make our request so make sure axios is installed. 
// If not use npm to install it or if you want to avoid installing it.
// Then just move this file to the frontend folder as axios is installed in there.
// Next Run this file:- "node node_getprofile_test.js"

import axios from 'axios';

var config = {
  method: 'get',
  url: 'http://localhost:5000/api/users/profile',
  headers: { 
    'Authorization': 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjYxMGZkNDlhMDExYTI5ZjhjNGEwMDRjOSIsImlhdCI6MTYyODQ2MTA3MiwiZXhwIjoxNjMxMDUzMDcyfQ.rIWBEfofElLdU7w4kga8phTAzsz3oiwTGQ5hMLWZ4M4'
  }
};

axios(config)
.then(function (response) {
  console.log(JSON.stringify(response.data));
})
.catch(function (error) {
  console.log(error);
});
