var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
    res.send(JSON.stringify({"status": 200, "tittle":"Express"}));
});

router.get('/mute/', function(req, res, next) {
    muted = !muted;
    res.send(JSON.stringify(JSON_data()));
});

router.get('/sensor/', function(req, res, next) {
    res.send(JSON.stringify(JSON_data()));
});

router.get('/changeTime/:time', function(req, res, next) {
    if(req.params.time != undefined && Number(req.params.time)!=NaN)
        wait_time = Number(req.params.time);
    res.send(JSON.stringify(JSON_data()));
});

function JSON_data(){
    return {"status": 200,
            "sensor_status" : sensor_status,
            "muted": muted,
            "wait_time":wait_time};
}

module.exports = router;
