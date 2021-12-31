
/*
Any note worthy changes with warts and all.


03-april-2003 ver 1.0.1 
	1) Accomodated identification of roaming GPRS cdrs

04-april-2003 ver 1.0.2 
	1) Changed the dump file access mode from "r+b" to "rb"



*/

/*

CREATE TABLE DYN_4_UDR ( 
  CHANGE_CONDITION_SGSN     NUMBER (3), 
  GGSN_ADDRESS              VARCHAR2 (20), 
  CHANGE_TIME_GGSN          VARCHAR2 (20), 
  CAUSE_FOR_REC_CLOSING     NUMBER (20), 
  MS_NETWORK_CAPABILITY     NUMBER (10), 
  DATA_DOWNLINK_GGSN        NUMBER (30), 
  IMSI                      VARCHAR2 (20), 
  RECORD_SEQUANCE_NO        NUMBER (20), 
  CHANGE_CONDITION_GGSN     NUMBER (3), 
  SERVED_PDP_ADDRESS        VARCHAR2 (20), 
  REGION_CODE_ID            VARCHAR2 (5), 
  QOS_NEGOTIATED_SGSN       VARCHAR2 (30), 
  ROAM                      NUMBER (1), 
  QOS_REQUESTED_SGSN        VARCHAR2 (30), 
  NETWORK_GROUP_ID          VARCHAR2 (5), 
  LOCATION_AREA_CODE        NUMBER (10), 
  RECORD_OPENING_TIME_GGSN  VARCHAR2 (20), 
  SGSN_ADDRESS              VARCHAR2 (20), 
  QOS_NEGOTIATED_GGSN       VARCHAR2 (30), 
  DATA_VOLUME               NUMBER (9), 
  ROUTING_AREA              VARCHAR2 (20), 
  DURATION                  NUMBER (20), 
  UPLINK_DOWNLINK           VARCHAR2 (10), 
  CELL_IDENTITY             NUMBER (10), 
  NODE_ID                   VARCHAR2 (20), 
  SERVED_MSISDN             VARCHAR2 (30), 
  CHARGING_ID               NUMBER (20), 
  ACCESS_POINT_NAME         VARCHAR2 (50), 
  DATA_UPLINK_GGSN          NUMBER (30), 
  CHANGE_TIME_SGSN          VARCHAR2 (20), 
  PDP_TYPE                  NUMBER (3), 
  RECORD_TYPE               NUMBER (3), 
  SERVICE_TYPE_ID           NUMBER (3)    NOT NULL, 
  FILE_ID                   NUMBER (9)    NOT NULL, 
  FILE_POS                  NUMBER (9)    NOT NULL, 
  CALL_TIME                 DATE          NOT NULL, 
  ROUTE_GROUP_ID            VARCHAR2 (5), 
  DAY_TYPE_ID               VARCHAR2 (5))

*/


