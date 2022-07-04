from pydoc_data.topics import topics
from flask import Flask
from flask import request
import boto3
import json

ACCESS_KEY = "AKIAQHM36E6CB6DQA3HP"
SECRETE_KEY = "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"

app = Flask(__name__)
client = boto3.client("iot-data",
                      aws_access_key_id=ACCESS_KEY,
                      aws_secret_access_key=SECRETE_KEY)


@app.route("/", methods=["GET", "POST"])
def index():
    # if request.method == "POST":
    print(request.json)
    client.publish(topic="led_ctrl", qos=1, payload=json.dumps(request.json))
    return "Hello World"
