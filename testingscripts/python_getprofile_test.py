# Objective:-
# This is a python script which tries to get the user's information. We
# send a bearer token along with us since the route is protected.

# How to use:-
# First, start your server.
# Go to your terminal/cmd and into this project's testingscripts folder. Run this python file:- "python3 python_getprofile_test.py"





import requests # This module may not be present by default. Use pip/pip3 to install.


url = "http://localhost:5000/api/users/profile"

payload={}
headers = {
  'Authorization': 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjYxMGZkNDlhMDExYTI5ZjhjNGEwMDRjOSIsImlhdCI6MTYyODQ2MTA3MiwiZXhwIjoxNjMxMDUzMDcyfQ.rIWBEfofElLdU7w4kga8phTAzsz3oiwTGQ5hMLWZ4M4'
}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)
