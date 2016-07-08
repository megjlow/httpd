new (function() {
	var ext = this;
	
	var descriptor = {
    	blocks: [
      	[' ', 'digital pin %m.pin setting %m.dsetting', 'setDigital', '1', 'off'],
      	[' ', 'pwm pin %m.ppin setting %n', 'setPwm', '1', '100'],
      	[' ', 'digital pin %m.pin get', 'getDigital', '1'],
      	[' ', 'pwm pin %m.ppin get', 'getPwm', '1']
	    ],
	    'menus': {
	    	'pin': ['1', '2', '3', '4'],
	      	'dsetting': ['on', 'off'],
	      	'ppin': ['1', '2']
		},
	 	url: 'https://github.com/savaka2/scratch-extensions/wiki/Link-Opener-extension'
	};
	
	ext._shutdown = function() {};
	
	ext._getStatus = function() {
    	return {status:2, msg:'Ready'};
  	};
  	
  	ext.getPwm = function(pin) {
  	};
  	
  	ext.setPwm = function(pin, setting) {
  	};
  	
  	ext.getDigital = function(pin) {
  	};
  	
  	ext.setDigital = function(setting, url) {
    	var url = 'http://%%%%%%/gpio2/' + setting; 
		console.log('setting' + setting);
		$.ajax({
			type: 'POST',
			url: url,
			success: function(response) {
		}
		});
	};

ScratchExtensions.register('Link Opener', descriptor, ext);})();
