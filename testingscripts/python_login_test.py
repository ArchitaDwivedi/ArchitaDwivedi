# Objective:-
# This is a python script to test and see if we can get back a response from
# our server after we have made a post request with some data.
# In this case, we want to get back details about a particular use after having
# sent that user's email and password in the post request's payload.

# How to use:-
# First, start your server.
# Go to your terminal/cmd and into this project's testingscripts folder. Run this python file:- "python3 python_login_test.py"


import requests # This module may not be present by default. Use pip/pip3 to install.
import json


#This is the route where we are doing a post request.
url = "http://localhost:5000/api/users/login"


#This is the JSON payload we send
payload = json.dumps({
  "email": "john@example.com",
  "password": "123456"
})
#This is the header that goes along with our request.
headers = {
  'Content-Type': 'application/json'
}


# We make a post request with our header and payload and get back a response
response = requests.request("POST", url, headers=headers, data=payload)


# Printing the response.
print(response.text)
