new (function() {
	var ext = this;
 
 	var getUrlParameter = function getUrlParameter(sParam) {
	    var sPageURL = decodeURIComponent(document.currentScript.src.split("?")[1]),
	        sURLVariables = sPageURL.split('&'),
	        sParameterName,
	        i;
	
	    for (i = 0; i < sURLVariables.length; i++) {
	        sParameterName = sURLVariables[i].split('=');
	
	        if (sParameterName[0] === sParam) {
	            return sParameterName[1] === undefined ? true : sParameterName[1];
	        }
	    }
	};
	  
	//var url = document.currentScript.src.split("?")[0];

	ext.name = getUrlParameter('name');
	ext.ip = getUrlParameter('ip');
	
	console.log('name ' + ext.name);
	console.log('ip ' + ext.ip);
	
	var descriptor = {
    blocks: [
      [' ', ext.name + ': digital pin %m.pin setting %m.dsetting', 'setDigital', '1', 'off'],
      [' ', ext.name + ': pwm pin %m.ppin setting %n', 'setPwm', '1', '100'],
      [' ', ext.name + ': digital pin %m.pin get', 'getDigital', '1'],
      [' ', ext.name + ': pwm pin %m.ppin get', 'getPwm', '1']
    ],
    'menus': {
      'pin': ['1', '2', '3'],
      'dsetting': ['on', 'off'],
      'ppin': ['1', '2']
     },
    url: 'https://github.com/savaka2/scratch-extensions/wiki/Link-Opener-extension'
  };

  ext._shutdown = function() {};
  ext._getStatus = function() {
    return {status: 2, msg: 'Device connected'};
  };

  ext.getPwm = function(pin) {
  };
  ext.setPwm = function(pin, setting) {
    var p = 4;
    if(pin == 2) {
      p = 5;
    }
    var url = 'http://' + ext.ip + '/gpio' + p + '/' + setting;
    $.ajax({
      type: 'POST',
      url: url,
      async: false,
      success: function(response) {
      }
    });
  };
  
  	ext.getDigital = function(pin) {
	};
	
<<<<<<< HEAD
	ext.setDigital = function(pin, setting) {
	    var s = 1;
	    if(setting == 'off') {
	      s = 0;
	    }
	    var p = 12;
	    if(pin == 1) {
	      p = 12;
	    }
	    else if(pin == 2) {
	      p = 13;
	    }
	    else if(pin == 3) {
	      p = 14;
	    }
	    p = 2;
	    var url = 'http://' + ext.ip + '/gpio' + p + '/' + s; 
=======
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
  		var s = 0;
  		if(setting == 'off') {
  			s = 1;
  		}
    	var url = 'http://%%%%%%/gpio2/' + s; 
		console.log('setting' + setting);
>>>>>>> branch 'master' of https://github.com/james-johnston/httpd.git
		$.ajax({
			type: 'POST', 
			url: url,
			async: false,
			success: function(response) {
			}
		});
	};
	
	ScratchExtensions.register(ext.name, descriptor, ext);

})();

