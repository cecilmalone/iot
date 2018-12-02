var http = require("http");
var express = require("express");
var app     = express();
var path    = require("path");
const server = http.createServer(app);

app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/dashboard.html'));
});

server.listen(3000, function listening() {
    console.log('Listening on %d', server.address().port);
});