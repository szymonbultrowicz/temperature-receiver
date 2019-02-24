#ifndef READING_H
#define READING_H

struct Reading {
    char mode;
    int16_t value;
    uint8_t crc;
    boolean valid;
};
#endif
