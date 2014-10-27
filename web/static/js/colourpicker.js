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
