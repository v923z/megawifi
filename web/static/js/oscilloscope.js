function get_timetrace() {
	$.ajax({
			type: 'POST',
			url: server_address, 
			data: JSON.stringify({type: 'command', command: 'C0N100N', format: 'binary'})
	})
	return false
}

$(document).ready(function() {
	var data = [[0, 0], [1, 1], [2, 1]]
	$.plot($('#div_graph'), [data])
})

function start_onclick(event) {
	var data = [[0, Math.random()], [1, Math.random()], [2, Math.random()], [3, Math.random()]]
	var plot = $.plot($('#div_graph'), [data])
}
