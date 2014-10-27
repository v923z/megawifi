function command_keypress(event) {
	console.log($('#input_command').val())	
	if(event.which == 13) {
		$.ajax({
			type: 'POST',
			url: server_address, 
			data: JSON.stringify({type: 'command', command: $('#input_command').val(), format: 'ascii'})
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
