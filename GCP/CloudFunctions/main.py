from google.cloud import pubsub_v1
import json

publisher = pubsub_v1.PublisherClient()
topic = "plant-watering-system-data"
project = "trim-heaven-415202"

def publish(request):
    try:
      request_json = request.get_json(silent=True)
      message = request_json['message']
      humidity = request_json['humidity']
      temperature = request_json['temperature']
      soil = request_json['soil']

      # References an existing topic
      topic_path = publisher.topic_path(project, topic)

      message_json = json.dumps(
          {
              "data": {"message": message},
          }
        )
      message_bytes = message_json.encode("utf-8")

      # Publishes a message
      publish_future = publisher.publish(topic_path, data=message_bytes, humidity=humidity, soil=soil, temperature=temperature)
      publish_future.result()  # Verify the publish succeeded
      return "Message published."
    except Exception as e:
      print(e)
      return (e, 500)