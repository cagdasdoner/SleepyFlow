
function HTML_connectionEstablished(uuid)
{
    $("#connectionDiv").html("Connected to MQTT Broker.<br>Unique ID : " + uuid);
    $('#subpubDiv').removeClass("hidden");
    $('#messageDiv').removeClass("hidden");
}

function HTML_showIncomingMessage(payload)
{
    $("#messageDiv").html("<b>Received</b> : " + payload);
}

$('#3deciliterButton').click(function(){
    MQTT_Publish(MQTT_TOPIC, "300");
});

$('#5deciliterButton').click(function(){
    MQTT_Publish(MQTT_TOPIC, "500");
});

$('#literButton').click(function(){
    MQTT_Publish(MQTT_TOPIC, "1000");
});

if(RUN_FOR_MOBILE)
{
    $('#manualButton').on('touchstart', function(){
        MQTT_Publish(MQTT_TOPIC, "start");
    });
    
    $('#manualButton').on('touchend',function(){
        MQTT_Publish(MQTT_TOPIC, "stop");
    });
}
else
{
    $('#manualButton').mouseup(function(){
        MQTT_Publish(MQTT_TOPIC, "stop");
    });
    
    $('#manualButton').mousedown(function(){
        MQTT_Publish(MQTT_TOPIC, "start");
    });
}

