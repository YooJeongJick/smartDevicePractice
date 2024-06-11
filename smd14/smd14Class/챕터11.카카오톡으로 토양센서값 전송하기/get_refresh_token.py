import requests
import json

url = 'https://kauth.kakao.com/oauth/token'
client_id = '자신의 REST 키값'
redirect_uri = 'https://example.com/oauth'
code = '자신의 CODE 값'

data = {
    'grant_type':'authorization_code',
    'client_id':client_id,
    'redirect_uri':redirect_uri,
    'code': code,
    }

response = requests.post(url, data=data)
tokens = response.json()

print(token)