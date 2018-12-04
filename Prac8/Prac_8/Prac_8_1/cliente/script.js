const base_URL = "http://localhost:1337";
const sensor_URL = base_URL+"/sensor/";
const mute_URL = base_URL+"/mute/";
const changeTime = base_URL+"/changeTime/"; 

$(document).ready(function(){

function downloadData() {
	$.ajax({
        dataType: "json",
        url: sensor_URL,
        success: function(data) {
			actualizar_datos(data)
        },
        error: function() {
            console.log("No se ha podido recibir información del sensor");
        }
    });
}

function actualizar_datos(data){
	$("#estado").html(data.sensor_status);
	$("#estado_alarma").html(data.muted.toString());
	$("#tiempo_espera").html(data.wait_time.toString());
			
	actualizar_switch(data);
}

function actualizar_switch(data){
	$("#switch").prop('checked', data.muted);
}

$("#waiting_time_submit").submit(function(){
	$.getJSON(changeTime+$("#waiting_time").val(), function(data){
		actualizar_datos(data)
	})
	.fail( function(){
		console.log("No se ha podido recibir información del sensor");
	});
});

$("#switch").click(function(){
	$.getJSON(mute_URL, function(data){
		actualizar_datos(data)
	})
	.fail( function(){
		console.log("No se ha podido recibir información del sensor");
	});
});

setInterval(downloadData,1000);

});