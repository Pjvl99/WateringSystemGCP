CREATE OR REPLACE DATABASE plant_watering_system;
CREATE OR REPLACE SCHEMA plant_watering_system.plant;

create or replace storage integration gcp_watering_system_gcs
  TYPE = EXTERNAL_STAGE
  STORAGE_PROVIDER = GCS
  ENABLED = TRUE
  STORAGE_ALLOWED_LOCATIONS = ('gcs://trim-heaven-415202/watering_system_data/sensor_data/');

  
create or replace file format plant_watering_system.plant.fileformat_plant
  TYPE = CSV
  SKIP_HEADER = 0;

CREATE OR REPLACE stage plant_watering_system.public.watering_system_stage
  STORAGE_INTEGRATION = gcp_watering_system_gcs
  URL = 'gcs://trim-heaven-415202/watering_system_data/sensor_data/'
  FILE_FORMAT = plant_watering_system.plant.fileformat_plant;

LIST @plant_watering_system.public.watering_system_stage;