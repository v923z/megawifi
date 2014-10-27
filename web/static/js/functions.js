$(document).ready(function () {
	$('.colourpicker').colpick({
		colorScheme:'dark',
		layout:'rgbhex',
		color:'ff8800',
		onSubmit:function(hsb,hex,rgb,el) {
			$(el).css('background-color', '#'+hex)
			submit_colour(el, rgb)
			$(el).colpickHide()
		}
	}).css('background-color', '#ff8800')
});

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
