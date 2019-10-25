const uint16_t pallet[] = { 0x0000, 0xD940, 0xFCC7, 0x04A0, 0x0411, 0xFE3B, 0x21DD, 0x5CBF, };

const uint8_t brick1_raw[] = {
	0x07, 0x77, 0x77, 0x70, 0x07, 0x77, 0x77, 0x70, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x74, 
	0x77, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x44, 0x77, 0x60, 0x66, 0x66, 0x66, 0x66, 0x06, 0x44, 
	0x77, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x44, 0x77, 0x66, 0x77, 0x77, 0x44, 0x44, 0x66, 0x44, 
	0x77, 0x66, 0x60, 0x00, 0x00, 0x00, 0x66, 0x44, 0x07, 0x66, 0x77, 0x77, 0x44, 0x44, 0x66, 0x40, 
	0x07, 0x66, 0x60, 0x00, 0x00, 0x00, 0x66, 0x40, 0x77, 0x66, 0x77, 0x77, 0x44, 0x44, 0x66, 0x44, 
	0x77, 0x66, 0x60, 0x00, 0x00, 0x00, 0x66, 0x44, 0x77, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x44, 
	0x77, 0x60, 0x66, 0x66, 0x66, 0x66, 0x06, 0x44, 0x77, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x44, 
	0x74, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x44, 0x44, 0x40, 0x04, 0x44, 0x44, 0x40, 
	};

const uint8_t brick2_raw[] = {
	0x00, 0x77, 0x77, 0x70, 0x00, 0x07, 0x70, 0x00, 0x07, 0x77, 0x74, 0x47, 0x77, 0x74, 0x44, 0x40, 
	0x77, 0x74, 0x44, 0x44, 0x44, 0x00, 0x00, 0x04, 0x07, 0x77, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 
	0x00, 0x00, 0x07, 0x77, 0x44, 0x40, 0x00, 0x00, 0x77, 0x77, 0x74, 0x44, 0x40, 0x00, 0x00, 0x40, 
	0x44, 0x74, 0x77, 0x00, 0x00, 0x04, 0x44, 0x44, 0x00, 0x04, 0x44, 0x40, 0x40, 0x00, 0x00, 0x00, 
	0x77, 0x00, 0x00, 0x07, 0x74, 0x40, 0x00, 0x44, 0x44, 0x77, 0x77, 0x74, 0x44, 0x44, 0x44, 0x44, 
	0x00, 0x47, 0x77, 0x77, 0x77, 0x00, 0x04, 0x40, 0x70, 0x04, 0x40, 0x00, 0x00, 0x00, 0x44, 0x40, 
	0x77, 0x00, 0x00, 0x44, 0x00, 0x44, 0x00, 0x00, 0x47, 0x77, 0x44, 0x44, 0x40, 0x00, 0x04, 0x44, 
	0x04, 0x44, 0x44, 0x40, 0x00, 0x00, 0x00, 0x44, 0x00, 0x04, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 
	};

const uint8_t brick3_raw[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};

const uint8_t brick4_raw[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x70, 0x07, 0x77, 0x70, 0x07, 0x70, 
	0x07, 0x44, 0x44, 0x00, 0x44, 0x40, 0x44, 0x40, 0x07, 0x47, 0x77, 0x77, 0x77, 0x77, 0x77, 0x40, 
	0x00, 0x47, 0x44, 0x44, 0x44, 0x44, 0x40, 0x40, 0x00, 0x07, 0x47, 0x77, 0x77, 0x77, 0x40, 0x00, 
	0x07, 0x07, 0x47, 0x44, 0x44, 0x40, 0x40, 0x40, 0x07, 0x47, 0x47, 0x47, 0x77, 0x40, 0x40, 0x40, 
	0x07, 0x47, 0x47, 0x47, 0x40, 0x40, 0x40, 0x40, 0x07, 0x47, 0x47, 0x40, 0x00, 0x40, 0x40, 0x00, 
	0x07, 0x47, 0x47, 0x44, 0x44, 0x70, 0x40, 0x40, 0x07, 0x07, 0x40, 0x00, 0x00, 0x00, 0x40, 0x40, 
	0x00, 0x47, 0x44, 0x44, 0x44, 0x44, 0x70, 0x40, 0x07, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
	0x07, 0x44, 0x40, 0x44, 0x44, 0x40, 0x04, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};

const uint8_t bullet_raw[] = {
	0x00, 0x11, 0x11, 0x00, 0x01, 0x10, 0x01, 0x10, 0x11, 0x05, 0x50, 0x11, 0x10, 0x53, 0x35, 0x01, 
	0x10, 0x53, 0x35, 0x01, 0x11, 0x05, 0x50, 0x11, 0x01, 0x10, 0x01, 0x10, 0x00, 0x11, 0x11, 0x00, 
	};

const uint8_t samus1_raw[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x11, 0x11, 0x11, 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x11, 0x31, 0x13, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x11, 0x13, 0x10, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x10, 0x01, 0x31, 0x10, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x22, 0x01, 0x11, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x22, 
	0x21, 0x12, 0x33, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x32, 0x22, 0x22, 0x33, 
	0x33, 0x30, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x23, 0x22, 0x22, 0x23, 0x33, 0x33, 0x30, 0x00, 
	0x00, 0x00, 0x01, 0x22, 0x22, 0x32, 0x21, 0x22, 0x20, 0x03, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x22, 0x22, 0x22, 0x31, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 
	0x23, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 
	0x12, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x12, 0x22, 0x20, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x13, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x12, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x22, 0x21, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x13, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x31, 0x10, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};

const uint8_t samus2_raw[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x11, 0x11, 0x11, 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x11, 0x31, 0x13, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x11, 0x13, 0x10, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x10, 0x01, 0x31, 0x10, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x22, 0x01, 0x11, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x22, 
	0x21, 0x12, 0x33, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x32, 0x22, 0x22, 0x33, 
	0x33, 0x30, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x23, 0x22, 0x22, 0x23, 0x33, 0x33, 0x30, 0x00, 
	0x00, 0x00, 0x01, 0x22, 0x22, 0x32, 0x21, 0x22, 0x20, 0x03, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x22, 0x22, 0x22, 0x31, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 
	0x23, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x22, 0x22, 0x22, 0x21, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 
	0x22, 0x22, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x00, 0x22, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x12, 0x21, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x22, 0x01, 0x13, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x21, 
	0x20, 0x01, 0x31, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x21, 0x10, 0x00, 0x01, 
	0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x22, 0x21, 0x00, 0x00, 0x00, 0x11, 0x11, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x31, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x13, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};

const uint8_t samus3_raw[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x11, 0x11, 0x11, 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x11, 0x31, 0x13, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x11, 0x13, 0x10, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x10, 0x01, 0x31, 0x10, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x22, 0x01, 0x11, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x22, 
	0x21, 0x12, 0x33, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x32, 0x22, 0x22, 0x33, 
	0x33, 0x30, 0x00, 0x00, 0x00, 0x01, 0x22, 0x22, 0x23, 0x22, 0x22, 0x23, 0x33, 0x33, 0x30, 0x00, 
	0x00, 0x00, 0x01, 0x22, 0x22, 0x32, 0x21, 0x22, 0x20, 0x03, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x22, 0x22, 0x22, 0x31, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 
	0x23, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 
	0x00, 0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x11, 0x00, 0x02, 0x22, 
	0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x13, 0x11, 0x10, 0x00, 0x22, 0x22, 0x22, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x13, 0x12, 0x22, 0x02, 0x22, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x11, 0x10, 0x11, 0x22, 0x12, 0x20, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 
	0x01, 0x22, 0x12, 0x20, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x21, 
	0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x02, 
	0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 
	0x33, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x11, 0x11, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 
	};

