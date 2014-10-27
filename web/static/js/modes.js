var server_address = 'http://127.0.0.1:8080'

var modes = new Array(
['Colour picker, 6 lights', '/colourpicker.mode'], 
['Stroboscope', '/stroboscope.mode']
)

$(document).ready(function () {
	$('aside').append('<ul id="ul_modes"></ul>')
	for(var i in modes) {
		$('#ul_modes').append('<li><a href=?mode=' + server_address + modes[i][1] + '>' + modes[i][0] + '</a></li>')
	}
});
