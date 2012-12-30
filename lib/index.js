var v8type = null;

try{
    v8type = require('../build/Release/v8type');
}catch(e){
    v8type = require('../build/Debug/v8type');
}

module.exports = v8type;