
typedef nx_struct th {
	nx_uint16_t temp;
	nx_uint16_t humi;
} th_t;

typedef nx_struct tsr {
	nx_uint16_t tsr;
} tsr_t;

typedef nx_struct vocs {
	nx_uint16_t vocs;
} vocs_t;


typedef nx_struct mode1_msg {
	th_t th;
	tsr_t tsr;
	vocs_t vocs;
} mode1_msg_t;

