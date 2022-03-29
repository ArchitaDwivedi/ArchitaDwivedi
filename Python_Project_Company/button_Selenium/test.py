import requests

BASE = "http://127.0.0.1:5000/"

resp = requests.get(BASE + "hello/192.168.1.110")

print(resp.json())