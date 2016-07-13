new (function() {
	var ext = this;
 
	  
	var params = window.location.search.replace(/^\?|\/$/g, '');
	var sparams = params.split('&');
	var name = '';
	var ip = '';
	$.each(sparams, function(index, element) {
		var p = element.split('=');
		if(p.length > 1) {
			if(p[0] == 'ip') {
				ip = p[1];
			}
			else if(p[0] == 'name') {
				name = p[1];
			}
		}
	});
	
	var descriptor = {
		blocks: [
			[' ', 'Load extension %s', 'loadExtension', '']
		]
	};
	
	ext._getStatus = function() {
        return {status: 2, msg: 'Ready'};
    };
    
    ext.loadExtension = function(url) {
    	ScratchExtensions.loadExternalJS(url);
    }
    
    ext._shutdown = function() {};
	

ScratchExtensions.register('LOADER', descriptor, ext);})();
