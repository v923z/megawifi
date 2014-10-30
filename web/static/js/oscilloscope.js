function get_timetrace(channel, samples, dt) {
	// channel:	channel identifier on MCU (0-3)
	// samples:	number of samples to collect (0-128)
	// dt: 		delay between samples (0-65535) [us]
	var timetrace = null
	var command = 'osc ' + channel + ' ' + samples + ' ' + dt + ';'
	$.ajax({
			type: 'POST',
			url: server_address, 
			data: JSON.stringify({type: 'command', command: command, format: 'binary', length: 2*samples})
			//success: function(data) {
				//// We have to parse the response here
				//timetrace = data.response
			//}
	})
	return timetrace
}

$(document).ready(function() {
	var data = [[0, 0], [1, 1], [2, 1]]
	$.plot($('#div_graph'), [data])
})

function start_onclick(event) {
	//var data = [[0, Math.random()], [1, Math.random()], [2, Math.random()], [3, Math.random()]]
	data = get_timetrace(0, 100, 1)
	var plot = $.plot($('#div_graph'), [data])
	alert(data)
}
