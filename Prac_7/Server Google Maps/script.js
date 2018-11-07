function initMap() {
    
    var mainMap = new google.maps.Map(document.getElementById('map'), {
        zoom: 17,
        center: {lat: 43.354839, lng: -5.851137}
    });

    console.log("Creando sensores...");
    var s1 = new Sensor(mainMap, {lat: 43.354839, lng: -5.851137}, 'Sensor 1', '192.168.61.204');
    var s2 = new Sensor(mainMap, {lat: 43.356091, lng: -5.853795}, 'Sensor 2', null);
    var s3 = new Sensor(mainMap, {lat: 43.352593, lng: -5.853424}, 'Sensor 3', null);
    var s4 = new Sensor(mainMap, {lat: 43.353079, lng: -5.850734}, 'Sensor 4', null);
}

function changeLed(state) {
    console.log("Cambiando a: " + (state ? "Encendido" : "Apagado"));
    var url = state ? 'ledOn' : 'ledOff';
    $.ajax({
        url: "http://192.168.61.204/" + url,
        error: function() {
            alert("No se ha podido cambiar el estado del LED");
        }
    });
}
