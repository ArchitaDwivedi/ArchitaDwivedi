# Objective:-
# This is a python script which sends data (post) and registers a user if they do not already exist.
# Once registered, we get back user details and a newly generated token so the user can immediately 
# go and login if they want to.

# How to use:-
# First, start your server.
# Go to your terminal/cmd and into this project's testingscripts folder. Run this python file:- "python3 python_register_test.py"


import requests # This module may not be present by default. Use pip/pip3 to install.
import json

url = "http://localhost:5000/api/users/"

payload = json.dumps({
  "name": "Jillian Doe",
  "email": "jillian@example.com",
  "password": "123456"
})
headers = {
  'Content-Type': 'application/json'
}

response = requests.request("POST", url, headers=headers, data=payload)

print(response.text)

