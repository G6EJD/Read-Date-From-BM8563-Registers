void BM8563::getDate(rtc_date_t *date) {
    uint8_t buf[4] = {0};

    Wire.beginTransmission(0x51);
    Wire.write(0x05);
    Wire.endTransmission();
    Wire.requestFrom(0x51, 4);

    while (Wire.available()) {
        buf[0] = Wire.read();
        buf[1] = Wire.read();
        buf[2] = Wire.read();
        buf[3] = Wire.read();
    }

    date->day  = Bcd2ToByte(buf[0] & 0x3f);
    date->week = Bcd2ToByte(buf[1] & 0x07);
    date->mon  = Bcd2ToByte(buf[2] & 0x1f);

    if (buf[2] & 0x80) {
        date->year = 1900 + Bcd2ToByte(buf[3] & 0xff);
    } else {
        date->year = 2000 + Bcd2ToByte(buf[3] & 0xff);
    }
}
