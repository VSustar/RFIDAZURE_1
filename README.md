# RFIDAZURE_1
 <br><br>
## Home Project of RFID tracking, MS Azure SQL Database storage and WebApp Presentation
 <br>
 <br>
        <p> The motive for the tracker is to keep track of items tagged with RFID tags.
            <br><span style="font-weight: bold">
            RFID tagged items are registered by RFID reader and ESP32 microcontroller. 
            <br>
            Each entry is sent to Azure cloud IoT hub by ESP32. </span>
            <br>
            IoT hub events are directed into Azure SQL database via Streaming analytics job. 
            <br>
            SQL database entries are queried by Python pypyodbc library. 
            <br>
            The data is processed and presented via Python Pandas, Plotly and Flask libraries on webpage hosted by Azure Web App.  </p>
            <br>
            
 <span align="middle"> <br>
 * This is the microcontroller part of the code for RFID tracking to AZURE SQL DB and WebAPP data presentation with Python Pandas, Plotly and Flask</span>  
<span align="left"><img src="https://github.com/VSustar/RFIDAZURE_1/blob/main/images/RFID%20diagram3_ESP32.png" width="100%"/></span>
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
See [Wiki](https://github.com/luc-github/ESP3D/wiki/Install-Instructions)
