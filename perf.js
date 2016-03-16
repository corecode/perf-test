var process = require('process');
var fs = require('fs');

var f = fs.openSync(process.argv[2], 'r');
var buf = new Buffer(4+2400*2*12/8);

var totalcoarse = 0;
var totalfine = 0;

for (;;) {
    var r = fs.readSync(f, buf, 0, buf.length, null);
    if (r <= 0)
        break;
    for (var i = 4; i < r - 3;) {
        var combined = buf[i++];
        combined |= buf[i++] << 8;
        combined |= buf[i++] << 16;
        var coarse = combined & 0xfff;
        var fine = combined >> 12;

        totalcoarse += coarse;
        totalfine += fine;
    }
}
