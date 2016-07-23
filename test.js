$(document).ready(function() {
	$('.on-off').on('click', function(e) {
		var self = $(this);
		var pin = self.data('pin');
		if(self.is(":checked")) {
			$.ajax({
				type: "POST",
				url: "http://" + location.host + "/gpio" + pin + "/1",
				complete: function() {
					$.ajax({
						type: "GET",
						url: "http://" + location.host + "/gpio" + pin,
						success: function(response) {
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
		}
		else {
			$.ajax({
				type: "POST",
				url: "http://" + location.host + "/gpio" + pin + "/0",
				complete: function() {
					$.ajax({
						type: "GET",
						url: "http://" + location.host + "/gpio" + pin,
						success: function(response) {
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
		}
	});
});
