#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>

#define SAMPLEFREQ 250000
#define DATALEN (SAMPLEFREQ*2*12/8)

struct blk {
        uint16_t voltage;
        uint16_t flags;
        uint8_t data[DATALEN];
};

struct blk buf;

int
main(int argc, char **argv)
{
        int f = open(argv[1], O_RDONLY);

        uint32_t totalcoarse = 0;
        uint32_t totalfine = 0;

        for (;;) {
                ssize_t r = read(f, &buf, sizeof(buf));

                if (r <= 0)
                        break;
                size_t datalen = r - 4;
                for (size_t i = 0; i < datalen - 3;) {
                        uint32_t combined = buf.data[i++];
                        combined |= buf.data[i++] << 8;
                        combined |= buf.data[i++] << 16;

                        uint32_t coarse = combined & 0xfff;
                        uint32_t fine = combined >> 12;

                        totalcoarse += coarse;
                        totalfine += fine;
                }
        }

        volatile int keep = totalcoarse + totalfine;

        return (0);
}
