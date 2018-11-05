function initMap() {
    var universidad = {lat: 43.354839, lng: -5.851137};
    var map = new google.maps.Map(document.getElementById('map'), {
        zoom: 17,
        center: universidad
    });

    var contentString = 'Hola que tal, soy un sensor tope de wapo colega';

    var infowindow = new google.maps.InfoWindow({
        content: contentString
    });

    var markerS1 = new google.maps.Marker({
        position: {lat: 43.354839, lng: -5.851137},
        map: map,
        title: 'Sensor 1'
    });
    
    markerS1.addListener('click', function() {
        infowindow.open(map, markerS1);
    });
    
    var markerS2 = new google.maps.Marker({
        position: {lat: 43.356091, lng: -5.853795},
        map: map,
        title: 'Sensor 1'
    });
    
    markerS2.addListener('click', function() {
        infowindow.open(map, markerS2);
    });
    
    var markerS3 = new google.maps.Marker({
        position: {lat: 43.352593, lng: -5.853424},
        map: map,
        title: 'Sensor 1'
    });
    
    markerS3.addListener('click', function() {
        infowindow.open(map, markerS3);
    });
    
    var markerS4 = new google.maps.Marker({
        position: {lat: 43.353079, lng: -5.850734},
        map: map,
        title: 'Sensor 1'
    });
    
    markerS4.addListener('click', function() {
        infowindow.open(map, markerS4);
    });
    
}