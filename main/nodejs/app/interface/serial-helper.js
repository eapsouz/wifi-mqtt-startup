'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});
exports.SerialHelper = undefined;

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _serialport = require('serialport');

var _serialport2 = _interopRequireDefault(_serialport);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var SerialHelper = exports.SerialHelper = function () {
    function SerialHelper() {
        _classCallCheck(this, SerialHelper);

        throw new Error('Cannot be Directly instantiated');
    }

    _createClass(SerialHelper, null, [{
        key: 'list',
        value: function list() {
            _serialport2.default.list(function (err, ports) {
                ports.forEach(function (port) {
                    console.log(port.comName);
                });
            });
        }
    }]);

    return SerialHelper;
}();
//# sourceMappingURL=serial-helper.js.map