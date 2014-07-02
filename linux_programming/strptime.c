#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char* chkValidUTF8(char * src)
{
	char * bytes = strdup(src);
	char * ret = bytes;

	while (*bytes != '\0') {
		char utf8 = *bytes;

		switch (0xf & (utf8 >> 4)) {
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07: {
			break;
		}

		case 0x08:
		case 0x09:
		case 0x0a:
		case 0x0b:
		case 0x0f: {
			*bytes = '?';
			break;
		}

		case 0x0c:
		case 0x0d:
		case 0x0e: {
			utf8 = *(++bytes);
			if (0x80 != (utf8 & 0xc0)) {
				*bytes = 0x80;
			}
		}
		}
		bytes++;
	}

	return ret;
}

int duration_to_int(char *s_dur)
{
	char * chkPropResDUR = chkValidUTF8(s_dur);
	int setDuration = 0;
	struct tm tm;
	strptime(chkPropResDUR, "%H:%M:%S", &tm);
	setDuration = (tm.tm_hour * 60 * 60 + tm.tm_min * 60 + tm.tm_sec) * 1;
	free(chkPropResDUR);
    return(setDuration);
}

int main(void)
{
	char *my_time = "1:2:3";
	int duration = duration_to_int(my_time);
	printf("\nduration = %d\n", duration);
}
