// Z:\home\vovan\bin\hid-descriptor-tool\xat_desc.hid.h


//char ReportDescriptor[426] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x00,                    // USAGE (Undefined)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x14,                    //   USAGE_PAGE (Alphnumeric Display)
    0x09, 0x20,                    //   USAGE (Display Attributes Report)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x01,                    //     REPORT_ID (1)
    0x09, 0x00,                    //     USAGE (Undefined)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x20,                    //     REPORT_COUNT (32)
    0xb1, 0x03,                    //     FEATURE (Cnst,Var,Abs)
    0x09, 0x35,                    //     USAGE (Rows)
    0x09, 0x36,                    //     USAGE (Columns)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0xb1, 0x03,                    //     FEATURE (Cnst,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x02,                    //     REPORT_ID (2)
    0x0b, 0x01, 0x00, 0x00, 0xff,  //     USAGE (Vendor Defined Page 1:Vendor Usage 1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x02,                    //     USAGE_MAXIMUM (Button 2)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x06,                    //     REPORT_COUNT (6)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x0d,                    //     USAGE_PAGE (Digitizers)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x17, 0x01, 0x00, 0x00, 0x80,  //     LOGICAL_MINIMUM (-2147483647)
    0x27, 0xff, 0xff, 0xff, 0x7f,  //     LOGICAL_MAXIMUM (2147483647)
    0x37, 0x01, 0x00, 0x00, 0x80,  //     PHYSICAL_MINIMUM (-2147483647)
    0x47, 0xff, 0xff, 0xff, 0x7f,  //     PHYSICAL_MAXIMUM (2147483647)
    0x75, 0x20,                    //     REPORT_SIZE (32)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x84,                    //   USAGE_PAGE (Power Device)
    0x09, 0x1e,                    //   USAGE (Flow)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x03,                    //     REPORT_ID (3)
    0x09, 0x30,                    //     USAGE (Voltage)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0x98, 0x3a,              //     LOGICAL_MAXIMUM (15000)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x46, 0xff, 0x03,              //     PHYSICAL_MAXIMUM (1023)
    0x67, 0x21, 0xd1, 0xf0, 0x00,  //     UNIT (SI Lin:Volts)
    0x75, 0x20,                    //     REPORT_SIZE (32)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x0d,                    //   USAGE_PAGE (Digitizers)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x04,                    //     REPORT_ID (4)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x15, 0x01,                    //     LOGICAL_MINIMUM (1)
    0x26, 0xe8, 0x03,              //     LOGICAL_MAXIMUM (1000)
    0x66, 0x12, 0xe0,              //     UNIT (SI Rot:Angular Accel)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x15, 0x01,                    //     LOGICAL_MINIMUM (1)
    0x26, 0xe8, 0x03,              //     LOGICAL_MAXIMUM (1000)
    0x66, 0x12, 0xf0,              //     UNIT (SI Rot:Angular Vel)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x0d,                    //   USAGE_PAGE (Digitizers)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x05,                    //     REPORT_ID (5)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x17, 0x01, 0x00, 0x00, 0x80,  //     LOGICAL_MINIMUM (-2147483647)
    0x27, 0xff, 0xff, 0xff, 0x7f,  //     LOGICAL_MAXIMUM (2147483647)
    0x37, 0x01, 0x00, 0x00, 0x80,  //     PHYSICAL_MINIMUM (-2147483647)
    0x47, 0xff, 0xff, 0xff, 0x7f,  //     PHYSICAL_MAXIMUM (2147483647)
    0x75, 0x20,                    //     REPORT_SIZE (32)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x06,                    //     REPORT_ID (6)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x02,                    //     USAGE_MAXIMUM (Button 2)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x03,              //     LOGICAL_MAXIMUM (1023)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x0d,                    //   USAGE_PAGE (Digitizers)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x07,                    //     REPORT_ID (7)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x17, 0x01, 0x00, 0x00, 0x80,  //     LOGICAL_MINIMUM (-2147483647)
    0x27, 0xff, 0xff, 0xff, 0x7f,  //     LOGICAL_MAXIMUM (2147483647)
    0x37, 0x01, 0x00, 0x00, 0x80,  //     PHYSICAL_MINIMUM (-2147483647)
    0x47, 0xff, 0xff, 0xff, 0x7f,  //     PHYSICAL_MAXIMUM (2147483647)
    0x75, 0x20,                    //     REPORT_SIZE (32)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x08,                    //     REPORT_ID (8)
    0x09, 0x3f,                    //     USAGE (Azimuth)
    0x09, 0x40,                    //     USAGE (Altitude)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x06,                    //     REPORT_COUNT (6)
    0x91, 0x03,                    //     OUTPUT (Cnst,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x14,                    //   USAGE_PAGE (Alphnumeric Display)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x10,                    //     REPORT_ID (16)
    0x09, 0x33,                    //     USAGE (Row)
    0x09, 0x34,                    //     USAGE (Column)
    0x09, 0x36,                    //     USAGE (Columns)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0x09, 0x2c,                    //     USAGE (Display Data)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x08,                    //     REPORT_COUNT (8)
    0x91, 0x00,                    //     OUTPUT (Data,Ary,Abs)
    0xc0,                          //   END_COLLECTION
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x11,                    //     REPORT_ID (17)
    0x09, 0x33,                    //     USAGE (Row)
    0x09, 0x34,                    //     USAGE (Column)
    0x09, 0x36,                    //     USAGE (Columns)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0x09, 0x2c,                    //     USAGE (Display Data)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x10,                    //     REPORT_COUNT (16)
    0x91, 0x00,                    //     OUTPUT (Data,Ary,Abs)
    0xc0,                          //   END_COLLECTION
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x12,                    //     REPORT_ID (18)
    0x09, 0x33,                    //     USAGE (Row)
    0x09, 0x34,                    //     USAGE (Column)
    0x09, 0x36,                    //     USAGE (Columns)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0x09, 0x2c,                    //     USAGE (Display Data)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x20,                    //     REPORT_COUNT (32)
    0x91, 0x00,                    //     OUTPUT (Data,Ary,Abs)
    0xc0,                          //   END_COLLECTION
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x85, 0x13,                    //     REPORT_ID (19)
    0x09, 0x33,                    //     USAGE (Row)
    0x09, 0x34,                    //     USAGE (Column)
    0x09, 0x36,                    //     USAGE (Columns)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
    0x09, 0x2c,                    //     USAGE (Display Data)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x3c,                    //     REPORT_COUNT (60)
    0x91, 0x00,                    //     OUTPUT (Data,Ary,Abs)
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
//};

