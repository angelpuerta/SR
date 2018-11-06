function initMap() {
    var universidad = {lat: 43.354839, lng: -5.851137};
    var map = new google.maps.Map(document.getElementById('map'), {
        zoom: 17,
        center: universidad
    });

    var contentString = 'Hola que tal, soy un sensor tope de wapo colega';

    var markerS1 = new google.maps.Marker({
        position: {lat: 43.354839, lng: -5.851137},
        map: map,
        title: 'Sensor 1'
    });
    
    var markerS2 = new google.maps.Marker({
        position: {lat: 43.356091, lng: -5.853795},
        map: map,
        title: 'Sensor 2'
    });
    
    var markerS3 = new google.maps.Marker({
        position: {lat: 43.352593, lng: -5.853424},
        map: map,
        title: 'Sensor 3'
    });
    
    var markerS4 = new google.maps.Marker({
        position: {lat: 43.353079, lng: -5.850734},
        map: map,
        title: 'Sensor 4'
    });
    
    setMarkerPopUp(map, markerS1, getData);
    setMarkerPopUp(map, markerS2, getRandomData);
    setMarkerPopUp(map, markerS3, getRandomData);
    setMarkerPopUp(map, markerS4, getRandomData);
}

function setMarkerPopUp(map, marker, dataGateway) {
    marker.addListener('click', function() {
        var infoWindow = new google.maps.InfoWindow({
            content: getContentString(dataGateway())
         });
        infoWindow.open(map, marker);
    });
}

function getContentString(data) {
    return `
        <p>Datos del sensor: </p>
        <p>Temperatura: ${data.temperatura.toFixed(2)}ºC</p>
        <p>Humedad: ${data.humedad.toFixed(2)}%</p>
        <button onclick="changeLed()">${getButtonText(data.led)}</button>
    `;
}

function getRandomData() {
    return {
        temperatura: Math.random() * 30,
        humedad: Math.random()
    }
}

function getButtonText(estado) {
    if (estado == true) 
        return "Apagar";
    else
        return "Encender";
}

function getData() {
    result = {
        temperatura: 0,
        humedad: 0,
        led: false
    };
    $.ajax({
        dataType: "json",
        url: "http://192.168.61.204/sensor",
        async: false,
        success: function(data) {
            result = data;
        },
        error: function() {
            alert("No se ha podido recibir información del sensor");
        }
    });
    return result;
}