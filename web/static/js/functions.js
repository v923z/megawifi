var server_address = 'http://127.0.0.1:8080'

function command_keypress(event) {
	console.log($('#input_command').val())	
	if(event.which == 13) {
		$.ajax({
			type: 'POST',
			url: server_address, 
			data: JSON.stringify({data: $('#input_command').val()})
		})
		return false
	} else {
		return true
	}
	return true
}

function submit_colour(el, rgb) {
	//alert(rgb)
}
