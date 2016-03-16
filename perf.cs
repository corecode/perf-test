using System;
using System.IO;

class main {
    static int Main(string[] args)
    {
        using (var f = File.Open(args[0], FileMode.Open)) {
            byte[] buf = new byte[2400*2*12/8+4];

            uint totalcoarse = 0;
            uint totalfine = 0;

            for (;;) {
                var r = f.Read(buf, 0, buf.Length);

                if (r <= 0)
                    break;

                for (int i = 4; i < r - 3;) {
                    uint combined = buf[i++];
                    combined |= (uint)buf[i++] << 8;
                    combined |= (uint)buf[i++] << 16;

                    uint coarse = combined & 0xfff;
                    uint fine = combined >> 12;

                    totalcoarse += coarse;
                    totalfine += fine;
                }
            }
        }

        return 0;
    }
}
