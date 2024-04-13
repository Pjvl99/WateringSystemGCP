from apache_beam.options.pipeline_options import PipelineOptions
from apache_beam.options import pipeline_options
from apache_beam import window
import apache_beam as beam
from apache_beam.runners.interactive.interactive_runner import InteractiveRunner
from datetime import datetime
import json
import pyarrow
import os

bucket_name = os.environ["BUCKET"]
project = os.environ["PROJECT_ID"]
topic = os.environ["TOPIC"]

def format_message(message, timestamp=beam.DoFn.TimestampParam):
    json_value = json.loads(message.data)
    value = str(datetime.utcfromtimestamp(float(timestamp)).strftime("%Y-%m-%d %H:%M:%S"),) + ","
    value += message.attributes['soil'] + "," + message.attributes['humidity'] + "," + message.attributes['temperature'] + "," + json_value['data']['message']
    return value

output_gcs = f'gs://{bucket_name}/watering_system_data/sensor_data'
with beam.Pipeline(options=PipelineOptions()) as p:
    (p
     | 'reading from topic' >> beam.io.ReadFromPubSub(topic=f"projects/{project}/topics/{topic}", with_attributes=True)
     | 'window' >> beam.WindowInto(
                         window.FixedWindows(300),
                         allowed_lateness=30)
     | 'format element' >> beam.Map(format_message)
     | 'GCS' >> beam.io.fileio.WriteToFiles(output_gcs, shards=1))
