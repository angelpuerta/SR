class Sensor {
    
    constructor(map, pos, name, ip) {
        this.map = map;
        this.name = name;
        this.ip = ip;
        this.marker = new google.maps.Marker({
            position: pos,
            map: map,
            title: name
        });
        this.infoWindow = new google.maps.InfoWindow({
            content: 'empty'
        });
        this.marker.addListener('click', this.displayDataInMarker.bind(this));
    }
    
    getUrl() {
        return "http://" + this.ip;
    }

    displayDataInMarker() {
        if (this.ip === null) {
            this.showInfo(this.getRandomData());
            return;
        }
		var urlSensor = this.getUrl() + "/sensor";
        $.ajax({
            dataType: "json",
            url: urlSensor,
            success: this.showInfo.bind(this, data),
            error: function() {
                alert("No se ha podido recibir información del sensor: " + t.name);
            }
        });
    }
        
    showInfo(data) {
        this.infoWindow.setContent(this.getMarkerHtmlContent(data));
        this.infoWindow.open(this.map, this.marker);
    }
    
    getRandomData() {
        return {
            temperatura: Math.random() * 30,
            humedad: Math.random(),
            led: false
        };
    }
    
    getMarkerHtmlContent(data) {
        var result = `
            <p>Datos de ${this.name}: </p>
            <p>Temperatura: ${data.temperatura.toFixed(2)}ºC</p>
            <p>Humedad: ${data.humedad.toFixed(2)}%</p>
            <p>Led: ${data.led ? 'Encendido' : 'Apagado'}</p>
            <button onclick="changeLed(true)">Encender</button>
            <button onclick="changeLed(false)">Apagar</button>
        `;
        return result;
    }
    
    
}