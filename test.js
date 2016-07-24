$(document).ready(function() {
$('.on-off').on('click', function(e) {
	var self = $(this);
	var pin = self.data('pin');
	if(self.is(":checked")) {
		$.ajax({
			type: "POST",
			url: "http://" + location.host + "/gpio" + pin + "/1",
			complete: function(data) {
				var response = jQuery.parseJSON(data);
				if(response.value == "1") {
					self.prop("checked", true);
				}
				else {
					self.prop("checked", false);
				}
			}
		});
	}
	else {
		$.ajax({
			type: "POST",
			url: "http://" + location.host + "/gpio" + pin + "/0",
			complete: function(data) {
				var response = jQuery.parseJSON(data);
				if(response.value == "1") {
					self.prop("checked", true);
				}
				else {
					self.prop("checked", false);
				}
			}
		});
	}
});
$('#run-test').on('click', function(e) {
	e.preventDefault();
	var pin = 2;
	window.setInterval(function() {
		var self = $('#run-test');
		var offon = 0;
		if(self.data("offon") == "0") {
			self.data("offon", "1");
			offon = 1;
		}
		else {
			self.data("offon", "0");
			offon = 0;
		}
		$.ajax({
			type: "POST",
			async: false,
			url: "http://" + location.host + "/gpio" + pin + "/" + offon,
			complete: function(data) {
				var response = jQuery.parseJSON(data);
				if(response.value == "1") {
					self.prop("checked", true);
				}
				else {
					self.prop("checked", false);
				}
			}
		});
	}, 500);
});
});
