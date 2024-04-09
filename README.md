# WateringSystemGCP

- The purpose of this data pipeline is to ingest data coming from sensors to snowflake in real time. The streaming job is using a fixed window of 30 minutes.

Diagram:

![Arduino_Snowflake](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/a2b6b41b-97f2-4ba7-9bf3-b1389aee77be)

- Steps to run this project:
  1. Create a GCP project then create a GCS bucket and finally set a pub/sub topic.
  2. Set your PROJECT_ID, BUCKET, TOPIC and SERVICE_ACCOUNT env variables.
  3. Deploy the cloud function and update the project name and topic variable.
  4. Set the cloud function url, ssid and password for your arduino script.
  5. Create another topic in pub/sub for GCS and create your own snowflake project
  6. Set the folders data inside snowflake and get the service accounts based on your bucket and pub/sub in order to give those service accounts the enough permissions for running in real time data from your GCS bucket.
  7. Run your dataflow job by using the following command: python3 GCP/Dataflow/watering_system.py \
--job_name='watering-system' \
--project=$PROJECT_ID \
--runner=DataflowRunner \
--temp_location $BUCKET/temp \
--region=$REGION \
--service_account_email $SERVICE_ACCOUNT

- This is how the cloud function look like:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/8ddf61a9-3a54-4b65-818d-30f3b0a1fa39)

- This is how the pub/sub topic for the sensor data look like:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/e04ce490-1c35-4b83-8745-5d1295ffb349)

- This is how the dataflow jobs look like:

![Screenshot from 2024-04-09 07-20-55](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/abe7af68-dcc7-41f2-b0b2-24b00b9708bf)

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/510a36d2-307c-48b2-aa2e-55d01923a539)

- This is the GCS output:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/1537c8c2-2455-4dba-8058-caf6cc8bc4e1)

- This is the pub/sub topic for snowflake:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/a69f5c4c-eb78-4289-83fa-4dbdf24e5f98)

- This is the output in snowflake:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/1347818d-57cf-4bbf-a0b8-08f57e1722d2)


![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/fe6cf258-2e93-4c1d-a489-074e15fb68c1)

- This is the final dashboard in snowsight:

![image](https://github.com/Pjvl99/WateringSystemGCP/assets/61527863/024fb45a-27b5-4cfa-ac25-b79a21c28f19)

