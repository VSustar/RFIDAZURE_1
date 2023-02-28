# RFIDAZURE_1
 <br><br>
## Home Project of RFID tracking, MS Azure SQL Database storage and WebApp Presentation
 <br> <br>
 The motive for the tracker is to keep track of items tagged with RFID tags. <br> <br>
            Project is compartmentalised into microcontroller (Esp32 in C) and cloud part (Azure IoTHub, SQL database and Python/HTML on Azure Webbapp). <br> <br>
            In this repository is the code for ESP32 microcontroller with required dependencies. 
 <br> <br>

            The sequence of whole process is as follows:

            1.RFID tagged items are registered by RFID reader and ESP32 microcontroller. 

            2.Each entry is sent to Azure cloud IoT hub by ESP32. </span>

            3.IoT hub events are directed into Azure SQL database via Streaming analytics job. 

            4.SQL database entries are queried by Python pypyodbc library. 

            5.The data is processed and presented via Python Pandas, Plotly and Flask libraries on webpage hosted by Azure Web App. 

            
 <span align="middle"> <br>
 * Microcontroller part of the code for RFID tracking to AZURE SQL DB and WebAPP data presentation with Python Pandas, Plotly and Flask</span>  
<span align="left"><img src="https://github.com/VSustar/RFIDAZURE_1/blob/main/images/RFID%20diagram3_ESP32_2.png" width="100%"/></span>
<br><br>
<span align="middle"> <br>
 * The diagram of pin connections for this code </span> <br>
<span align="left"><img src="https://github.com/VSustar/RFIDAZURE_1/blob/main/images/RFID%20diagram3ESP32_PINS.png" width="50%"/></span> 
<br>

| DEVICE        | ESP32(38pin version| RFID-RC522 |
| ------------- |:-------------:| -----:|
| pin           | 3V3| 3.3V |
| pin      | GND      |  GND |
| pin|D2    |   RST |
|pin    | D5    |  SDA |
|pin | D18     |   SCK|
|pin    | D19    |  MISO |
|pin | D23   |   MOSI|


<br><br>
<span align="middle"><br> 
 * Actuall setup photo of RFID reader with ESP32 connected via breadboard</span>  
<span align="left"><img src="https://github.com/VSustar/RFIDAZURE_1/blob/main/images/IMG_20230228_105013_647.jpg" width="50%"/></span>

### Link to the Webpage part of the code
See [Github](https://github.com/VSustar/RFIDAZURE_2)
#### Link to the Vid Sustar's RFID tracker WebPage
See [Webpage](https://sustariot.azurewebsites.net/)
