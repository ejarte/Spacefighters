#include "network.h"

char ip_substr[30][10];

bool validateIPv4Entry(char* str)
{
	for (int i = 0; i < 30; i++) {
		ip_substr[i][0] = '\0';
	}
	int min, max, k;
	min = 0;
	k = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		max = i;
		if (!(isDigit(str[i]) || str[i] == '.')) {
			return false;
		}
		if (str[i] == '.') {
			if (i - min > 3) {
				return false;
			}
			else {
				strcpy(ip_substr[k], substring(str, min, max));
				printf("sub: %s\n", ip_substr[k]);
				min = i + 1;
				k++;
			}
		}
	}
	if (k == 3) {
		max += 1;
		strcpy(ip_substr[k], substring(str, min, max));
		for (int i = 0; i < 4; i++) {
			k = atoi(ip_substr[i]);
			if (k < 0 || k > 255) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool validatePort(char* str, Uint16* port)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isDigit(str[i])) {
			printf("%c is not a digit (%d)\n", str[i], i);
			return false;
		}
	}
	*port = atoi(str);
	return true;
}

void printIpInfo(IPaddress* ip)
{
	Uint8 byte[4];
	Uint16 port = ip->port;
	Uint32 ip_adr = ip->host;
	Uint8 *p = (Uint8 *)&ip_adr;
	byte[0] = p[0];
	byte[1] = p[1];
	byte[2] = p[2];
	byte[3] = p[3];
	printf("ip: %d.%d.%d.%d\n", byte[0], byte[1], byte[2], byte[3]);
}