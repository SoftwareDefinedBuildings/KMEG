// define NONE or WEP or WPA
#define NONE
//#define WPA

#define DHCP TRUE // DHCP : TRUE, STATIC : FALSE
// "ip addr,Subnet mask, Gateway" 
#define IPADDR "192.168.13.2,255.255.255.0,192.168.13.1"
#define SSID "aalto open"
//#define SSID "keti_tinyos_01"
#define SECCODE "" // smart
//#define SECCODE "allberkeley" // smart
#define IPPORT "222.239.78.8,1117"		// "ip addr,port" // Taijoon
//#define SSID "keti_tinyos_01"
//#define SECCODE "allberkeley" // smart
//#define IPPORT "222.239.78.8,1117"		// "ip addr,port" // Taijoon

//#define IPPORT "222.239.78.8,8282"		// "ip addr,port" // 
//#define IPPORT "192.168.0.3,9999"		// "ip addr,port" // GSBC


enum {
		STATE_0 = 0,
		STATE_1 = 1,
		STATE_2 = 2,
		STATE_3 = 3,
		STATE_4 = 4,
		STATE_5 = 5,
		STATE_6 = 6,
		STATE_7 = 7,
		STATE_8 = 8,
		STATE_9 = 9,
		STATE_10 = 10
};
