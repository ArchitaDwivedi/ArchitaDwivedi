# Objective:-
# This is a python script to GET one product using id

# How to use:-
# First, start your server.
# Go to your terminal/cmd and into this project's testingscripts folder. Run this python file:- "python3 python_fetchone_test.py"



import requests # This module may not be present by default. Use pip/pip3 to install.

url = "http://localhost:5000/api/products/610fd49a011a29f8c4a004cc"

payload={}
headers = {}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)
