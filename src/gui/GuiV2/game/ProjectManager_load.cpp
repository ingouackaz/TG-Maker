
#include <SFML/Graphics/Image.hpp>

#include "ImportProject.hpp"

void ProjectManager::_init_resources()
{
static const unsigned char player_png[871] = {
0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7A, 0x7A,
0xF4, 0x00, 0x00, 0x00, 0x06, 0x62, 0x4B, 0x47, 0x44, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xA0,
0xBD, 0xA7, 0x93, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0B, 0x13, 0x00,
0x00, 0x0B, 0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0x07, 0x74, 0x49, 0x4D, 0x45,
0x07, 0xDD, 0x04, 0x0E, 0x11, 0x37, 0x28, 0xCF, 0x7D, 0xB5, 0x2B, 0x00, 0x00, 0x02, 0xF4, 0x49,
0x44, 0x41, 0x54, 0x58, 0xC3, 0xED, 0x94, 0x4D, 0x68, 0x5C, 0x55, 0x18, 0x86, 0x9F, 0xF3, 0x73,
0xEF, 0xCD, 0x38, 0x99, 0x4C, 0x92, 0x99, 0xC4, 0xFE, 0x89, 0xC5, 0x62, 0x54, 0x2C, 0x45, 0x11,
0xA1, 0x0A, 0x22, 0x82, 0x14, 0xAC, 0x56, 0x41, 0x28, 0x08, 0xEE, 0x4A, 0x37, 0xDA, 0xFA, 0xB3,
0x70, 0x5B, 0x17, 0x5A, 0x28, 0x41, 0xF0, 0x07, 0x17, 0x52, 0x24, 0xE0, 0x0F, 0x05, 0xB1, 0x8B,
0x58, 0x04, 0x09, 0x48, 0xA1, 0x56, 0x6D, 0x70, 0xA1, 0xB4, 0xD5, 0x60, 0x2A, 0x68, 0xAD, 0xC6,
0x50, 0x69, 0x33, 0x99, 0x49, 0x33, 0x77, 0xEE, 0xE4, 0xDE, 0x73, 0x3E, 0x17, 0x1D, 0x4B, 0xA1,
0x9B, 0xDE, 0xE2, 0x5D, 0x08, 0x79, 0x57, 0x87, 0x0F, 0xCE, 0xFB, 0xBD, 0xE7, 0x7B, 0xDF, 0xF3,
0xC1, 0x2A, 0x56, 0x71, 0x03, 0x58, 0x98, 0x7E, 0xFD, 0x3F, 0xE3, 0x52, 0x37, 0x7A, 0xF1, 0xE2,
0x89, 0xD7, 0x26, 0x80, 0x5D, 0x4A, 0x5D, 0x43, 0xB1, 0xBE, 0xF6, 0xC0, 0xBE, 0xF9, 0xEB, 0xE5,
0xB1, 0x79, 0x1B, 0xCF, 0x1E, 0xD9, 0xAB, 0x6C, 0x10, 0xBC, 0xD5, 0x6A, 0x2E, 0xEE, 0xAC, 0x54,
0x06, 0x30, 0xF6, 0x1A, 0x8A, 0x0F, 0x80, 0x6D, 0xD7, 0xCB, 0xA7, 0xF3, 0xCF, 0x4C, 0x19, 0x97,
0x65, 0x2F, 0x29, 0xA5, 0xFA, 0xAD, 0x35, 0x18, 0x7D, 0x79, 0x02, 0x5A, 0x29, 0x8C, 0xD1, 0x00,
0xA5, 0x3C, 0x74, 0xB9, 0x05, 0x88, 0x08, 0x22, 0x82, 0xB5, 0xA1, 0x7A, 0x71, 0x7C, 0x8A, 0xBD,
0x07, 0xBE, 0xC0, 0x8B, 0x30, 0x31, 0xF9, 0x03, 0x4F, 0xEC, 0x39, 0x44, 0x73, 0x29, 0xC9, 0xC5,
0x97, 0xDB, 0x02, 0x44, 0xB0, 0x41, 0x80, 0xB1, 0x01, 0x2B, 0xA9, 0xBB, 0x52, 0xCE, 0x9C, 0xA7,
0xBB, 0x92, 0x21, 0x48, 0xB1, 0x21, 0xFC, 0xF9, 0xB3, 0x3D, 0x36, 0x8A, 0xA2, 0xB4, 0xBF, 0xBF,
0x82, 0xEF, 0x5D, 0xB7, 0x46, 0xE3, 0xBC, 0xE0, 0xBD, 0x10, 0x58, 0xFD, 0x4D, 0xFD, 0xC1, 0x57,
0x1F, 0x2A, 0x6E, 0x02, 0x40, 0x96, 0x65, 0x38, 0xE7, 0x64, 0x70, 0x68, 0x50, 0x1D, 0x9E, 0x9C,
0x22, 0x08, 0x2C, 0x2E, 0x73, 0xEC, 0xD8, 0xFE, 0x08, 0x59, 0xE6, 0x28, 0x34, 0x03, 0x4A, 0xEB,
0x2C, 0xF3, 0xFE, 0xBD, 0xB8, 0xD3, 0x51, 0x07, 0x27, 0x3E, 0xE1, 0x9E, 0x2D, 0x77, 0x31, 0xB6,
0x69, 0x23, 0x9B, 0xEF, 0x1E, 0xE3, 0xDD, 0x83, 0x87, 0x24, 0x8E, 0x93, 0xE2, 0x04, 0xCC, 0x4C,
0x3E, 0xAF, 0x50, 0xE6, 0x96, 0x38, 0x4E, 0x9E, 0x69, 0x34, 0x16, 0xF9, 0xF5, 0xEC, 0x9F, 0xAC,
0x19, 0xAD, 0x53, 0xAF, 0x0D, 0x71, 0xF3, 0x48, 0x8D, 0xB3, 0xBF, 0xCF, 0xA9, 0x34, 0xCB, 0x1A,
0x85, 0x85, 0xB0, 0xAF, 0x5C, 0xBD, 0x3D, 0xED, 0x26, 0x67, 0x40, 0x49, 0xA3, 0xD9, 0x62, 0xA0,
0x52, 0x66, 0xDF, 0xFE, 0x77, 0xAE, 0x84, 0x49, 0x6B, 0xC3, 0xD1, 0x63, 0xD3, 0x2F, 0x14, 0x26,
0x40, 0x6B, 0xF3, 0x51, 0x54, 0x2A, 0x8B, 0x73, 0xA9, 0x1A, 0xAA, 0x96, 0x79, 0xFA, 0xC9, 0x47,
0x01, 0x30, 0x5A, 0x33, 0x7F, 0xFE, 0x22, 0x3F, 0xFD, 0x32, 0x27, 0xDB, 0xB7, 0x3D, 0xFC, 0x29,
0x07, 0x8E, 0x6F, 0x2D, 0x2A, 0x84, 0x29, 0xA0, 0x44, 0x3C, 0x25, 0x3D, 0x48, 0x78, 0x53, 0x80,
0x28, 0xC7, 0xFC, 0xF9, 0x05, 0x4E, 0xCE, 0x9E, 0xE3, 0xBE, 0xCD, 0x9B, 0x54, 0x6B, 0xF1, 0x42,
0x5A, 0x68, 0x08, 0xFF, 0x1D, 0xB7, 0xB7, 0x09, 0x1E, 0x47, 0x3B, 0x4E, 0xF8, 0xF2, 0xF8, 0x49,
0xC4, 0xC3, 0x86, 0x75, 0x23, 0x2C, 0x2F, 0xB7, 0x0A, 0x5E, 0x44, 0x40, 0x10, 0x86, 0x5C, 0xBA,
0xD4, 0xA6, 0xD5, 0x4E, 0x39, 0x32, 0x75, 0x82, 0x28, 0x0A, 0xD9, 0xB0, 0xB6, 0x8E, 0xD6, 0x86,
0x9C, 0x7B, 0x28, 0x9F, 0x00, 0xB9, 0xFC, 0x7A, 0x59, 0x68, 0xB6, 0xD5, 0x57, 0xD3, 0x33, 0x2C,
0x2E, 0x75, 0x70, 0x5E, 0x68, 0xC7, 0x5D, 0x4E, 0xCD, 0xFC, 0xC6, 0xFD, 0xF7, 0x8E, 0x49, 0xDE,
0xC7, 0xE4, 0xB2, 0x40, 0x89, 0x8C, 0x2B, 0x49, 0xD5, 0xD1, 0xAF, 0x4F, 0x31, 0xF7, 0x77, 0x13,
0x6B, 0x14, 0x4A, 0x6B, 0xBC, 0x08, 0xC6, 0x68, 0xBE, 0xFD, 0x6E, 0x46, 0x2D, 0xC7, 0xDD, 0xF1,
0xC2, 0x56, 0xF1, 0xEE, 0xC7, 0x37, 0xAE, 0x8B, 0x02, 0xF3, 0x97, 0x13, 0xA8, 0x56, 0x4A, 0x24,
0xDD, 0x94, 0xBE, 0xC8, 0x62, 0x8D, 0xA1, 0xD4, 0x17, 0x90, 0x24, 0x29, 0x40, 0x6D, 0xFF, 0x87,
0xA7, 0x1B, 0x85, 0x58, 0x10, 0x77, 0x56, 0x3E, 0x76, 0xDE, 0x52, 0x29, 0x47, 0x44, 0xA1, 0x45,
0xBC, 0xC7, 0x6A, 0x4D, 0x9A, 0x3A, 0x92, 0x6E, 0x4A, 0x96, 0x79, 0x0A, 0xB5, 0xA0, 0x14, 0x05,
0xC7, 0xC2, 0xC0, 0xB0, 0x76, 0x74, 0x98, 0x91, 0xE1, 0x01, 0x32, 0x6F, 0x08, 0x43, 0xCB, 0x9A,
0x91, 0x2A, 0xA3, 0xF5, 0x2A, 0xD6, 0x68, 0xAC, 0x51, 0x14, 0x62, 0xC1, 0xAE, 0xC7, 0x6E, 0xE5,
0x95, 0xE7, 0x9E, 0xAA, 0xB6, 0x96, 0xE2, 0x66, 0xB9, 0x14, 0x21, 0x90, 0x7E, 0xFF, 0xE3, 0x1F,
0x3B, 0x2B, 0x65, 0xC3, 0x1D, 0xB7, 0xAD, 0x3F, 0x8C, 0x52, 0x41, 0xDC, 0xE9, 0x02, 0xD4, 0xB6,
0x3E, 0xFB, 0x7E, 0xA3, 0x90, 0x0C, 0xCC, 0x7E, 0xFE, 0xF2, 0x30, 0xB0, 0x70, 0xD5, 0xA7, 0xD8,
0xD2, 0x3B, 0x9F, 0xBE, 0x8A, 0xAB, 0x76, 0xE7, 0x8E, 0xB7, 0x1B, 0x45, 0xED, 0x81, 0x04, 0x78,
0xB3, 0xD7, 0xDC, 0x01, 0x17, 0x7A, 0xF5, 0x37, 0x00, 0xD3, 0x13, 0x91, 0xB0, 0x8A, 0x55, 0xFC,
0x9F, 0xF0, 0x0F, 0x76, 0xE2, 0x19, 0x83, 0xEB, 0xE7, 0x43, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x49,
0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

static const unsigned char tile_jpg[775] = {
0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x08, 0x02, 0x00, 0x00, 0x00, 0xFC, 0x18, 0xED,
0xA3, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B,
0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0x07, 0x74, 0x49, 0x4D, 0x45, 0x07, 0xDD,
0x04, 0x0A, 0x11, 0x36, 0x36, 0xA3, 0x0B, 0x2E, 0x5E, 0x00, 0x00, 0x02, 0xA6, 0x49, 0x44, 0x41,
0x54, 0x48, 0xC7, 0xED, 0x56, 0xCB, 0xAE, 0x1C, 0x45, 0x0C, 0xB5, 0x5D, 0xAF, 0xEE, 0x54, 0x67,
0x08, 0xC9, 0x45, 0x44, 0x80, 0x90, 0x90, 0xB2, 0xE2, 0x13, 0xF8, 0x37, 0xFE, 0x80, 0x7F, 0x63,
0x87, 0xD8, 0x81, 0x40, 0x42, 0x42, 0x82, 0xDC, 0xDC, 0x99, 0x3B, 0xD5, 0x5D, 0x0F, 0xDB, 0x2C,
0x7C, 0x35, 0xBB, 0x91, 0xE8, 0x51, 0xEE, 0x2E, 0x5E, 0x59, 0x5D, 0x6D, 0x1F, 0xFB, 0xB8, 0x1E,
0x07, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0xE6, 0x79, 0x26, 0x22, 0x22, 0x72, 0xCE, 0xC1, 0x4E,
0x73, 0xCE, 0x59, 0xEC, 0x3C, 0xCF, 0xF6, 0xE5, 0x29, 0xED, 0x34, 0x4D, 0x39, 0x67, 0x44, 0xB4,
0x05, 0xF3, 0x53, 0x4A, 0x7B, 0x01, 0x52, 0x4A, 0x88, 0x98, 0x73, 0xB6, 0x42, 0xCD, 0x9F, 0xA6,
0x09, 0x88, 0xC8, 0x3E, 0x85, 0x10, 0xAC, 0x10, 0x73, 0x6E, 0xB0, 0x10, 0x82, 0xB5, 0x1E, 0x42,
0xB0, 0x72, 0x89, 0x08, 0x52, 0x4A, 0x87, 0xC3, 0x01, 0x00, 0x6A, 0xAD, 0xAA, 0xAA, 0xAA, 0xBD,
0x77, 0xBD, 0xC9, 0x2E, 0x81, 0xB5, 0x56, 0x00, 0x38, 0x1C, 0x0E, 0x29, 0x25, 0x5F, 0x6B, 0x35,
0xEE, 0x62, 0x8C, 0xCC, 0x2C, 0x22, 0x22, 0xD2, 0x7B, 0xBF, 0x50, 0xF9, 0x3F, 0x6D, 0x5D, 0x57,
0x22, 0x52, 0x55, 0x4B, 0x45, 0x44, 0xBD, 0xF7, 0x5A, 0x2B, 0xD9, 0x70, 0x44, 0xC4, 0xF8, 0x51,
0x55, 0x1B, 0xC0, 0xDE, 0xF2, 0x6D, 0x0C, 0xAA, 0x6A, 0x2C, 0x89, 0xC8, 0xD3, 0x66, 0xF1, 0xDE,
0x03, 0xC0, 0xB2, 0x2C, 0xD6, 0x5A, 0x29, 0xE5, 0x78, 0x3C, 0xDE, 0x46, 0xD1, 0xF1, 0x78, 0x2C,
0xA5, 0x18, 0xD5, 0xCB, 0xB2, 0x00, 0x3C, 0x25, 0x07, 0x44, 0x24, 0xA2, 0x6D, 0xDB, 0x54, 0x95,
0x99, 0xED, 0xD7, 0x1B, 0xB2, 0x5F, 0xC2, 0xB7, 0x6D, 0x23, 0x22, 0xDB, 0xA6, 0x68, 0x00, 0xAA,
0x2A, 0x22, 0xE6, 0xD8, 0xC2, 0xDF, 0x03, 0xBE, 0xF4, 0xE7, 0x73, 0xF7, 0xD9, 0xF7, 0x21, 0xFE,
0xCC, 0xE9, 0x65, 0x40, 0x50, 0x59, 0x89, 0xB9, 0xAE, 0x19, 0xD5, 0x85, 0x58, 0x64, 0x06, 0x84,
0x17, 0xB4, 0xFE, 0xDB, 0xFD, 0x9B, 0x10, 0x8C, 0x58, 0x4B, 0x62, 0x00, 0xAA, 0x4A, 0xD7, 0x86,
0xF6, 0xC6, 0xB3, 0x0E, 0x99, 0x42, 0x60, 0x88, 0x82, 0x21, 0x47, 0x14, 0x6E, 0x44, 0x9C, 0x1F,
0x7F, 0x5D, 0x92, 0xAB, 0xF1, 0xB3, 0xD6, 0xE4, 0x85, 0x56, 0xA7, 0xD2, 0x06, 0xBC, 0x0E, 0x72,
0x2D, 0xCF, 0x55, 0x00, 0x5F, 0xEF, 0x2B, 0x23, 0xC1, 0xA8, 0xE0, 0x59, 0x01, 0x75, 0x08, 0x37,
0x61, 0x1E, 0xEE, 0xF3, 0xA6, 0x4E, 0x01, 0xC4, 0x67, 0xF0, 0x14, 0x50, 0x9A, 0x38, 0x84, 0xB1,
0x1B, 0x40, 0x58, 0x31, 0x2D, 0xD8, 0xD7, 0x84, 0x14, 0x49, 0x7B, 0xEF, 0x31, 0x25, 0x76, 0xD3,
0xEF, 0xF3, 0x37, 0xEF, 0x2B, 0xC5, 0xED, 0x9E, 0x1C, 0x6C, 0xE2, 0x10, 0x18, 0x43, 0x64, 0xF1,
0xBB, 0x01, 0xFA, 0x7C, 0x57, 0x01, 0xC6, 0x7A, 0xD6, 0xED, 0x9E, 0x78, 0x85, 0x38, 0xCB, 0xF6,
0x50, 0x14, 0xDE, 0xF1, 0xFB, 0xBB, 0x29, 0xA2, 0xF4, 0x56, 0x1E, 0x7A, 0x2B, 0x48, 0x80, 0x08,
0x83, 0xF5, 0x2A, 0x13, 0x57, 0xEF, 0x96, 0xD3, 0x9F, 0x67, 0x7A, 0xE5, 0x0E, 0x5F, 0x6C, 0x10,
0x5C, 0x3F, 0x4E, 0x1F, 0x7E, 0xD1, 0x9F, 0x7E, 0x58, 0x1E, 0x1F, 0x7E, 0xD3, 0xE5, 0xEE, 0xC7,
0x9F, 0xD3, 0xDD, 0xBB, 0x85, 0x1F, 0x80, 0x5B, 0xDF, 0xF8, 0x88, 0xE9, 0xED, 0x0D, 0x33, 0xA8,
0x87, 0x6F, 0x53, 0x4A, 0x08, 0x23, 0x49, 0x61, 0xF0, 0xEB, 0xAB, 0xEF, 0xFF, 0x2A, 0xE1, 0x0F,
0xF7, 0xD5, 0x77, 0xF0, 0x98, 0x5F, 0xBF, 0xFD, 0x20, 0xD0, 0xD6, 0x33, 0xC4, 0x18, 0xA6, 0x69,
0xF2, 0x00, 0x75, 0xDB, 0xDD, 0x41, 0x1B, 0xF5, 0x65, 0xD0, 0xD6, 0x47, 0x08, 0x93, 0xAA, 0x32,
0xC0, 0xD7, 0xF2, 0x0F, 0x10, 0x6C, 0xC1, 0x1F, 0x61, 0x11, 0x84, 0xB8, 0xE4, 0x33, 0x64, 0xDA,
0x4E, 0x79, 0x4A, 0xE0, 0xAF, 0xDE, 0xBE, 0x57, 0xCF, 0xC1, 0x6D, 0xB6, 0xE3, 0x1C, 0x7C, 0x2C,
0xFB, 0x04, 0xF0, 0x09, 0xE0, 0xA3, 0x01, 0x10, 0x51, 0x6B, 0xCD, 0x36, 0x32, 0x00, 0x9C, 0x4E,
0xA7, 0xBD, 0x89, 0x2C, 0xC4, 0xC2, 0x5B, 0x6B, 0x26, 0x56, 0xE0, 0xF2, 0xAA, 0x3D, 0xE3, 0x93,
0xE9, 0x9C, 0x33, 0xB5, 0x74, 0x51, 0x1C, 0xAA, 0x5A, 0x4A, 0x91, 0x9D, 0x56, 0x4A, 0xB9, 0x84,
0x5B, 0x1F, 0x39, 0x67, 0xE7, 0x9C, 0x37, 0xA9, 0x62, 0x1D, 0x31, 0x33, 0x22, 0x9A, 0xAA, 0xB9,
0xE1, 0xC2, 0x30, 0x05, 0xC4, 0xCC, 0x17, 0xA5, 0xC2, 0xCC, 0x3E, 0xA5, 0x14, 0x42, 0x58, 0xD7,
0xB5, 0xB5, 0x16, 0x63, 0x74, 0xCE, 0x8D, 0x31, 0x6E, 0x90, 0x8E, 0xF3, 0x3C, 0x8F, 0x31, 0x8C,
0xF0, 0xD6, 0x9A, 0x88, 0x84, 0x10, 0x44, 0xE4, 0xF9, 0xA5, 0xE3, 0xB3, 0x8B, 0xDF, 0xE7, 0x96,
0xEF, 0xFF, 0x01, 0x06, 0xCA, 0xF4, 0xE2, 0xB4, 0xF7, 0xAB, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x49,
0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

    ImageManager::singleton().buffers().set_buffer(0, reinterpret_cast<char const*>(tile_jpg));
    ImageManager::singleton().buffers().set_buffer(1, reinterpret_cast<char const*>(player_png));
    debug("resources initialized\n");
}


#define Manager Manager
#define import(element, var) element##Manager& var(element##Manager::singleton())

void ProjectManager::load_new_game()
{
    _init_resources();
    
    debug("loading the debug map\n");
    import(Action, am);
    import(Branch, bm);
    import(Event, em);
    import(Image, im);
    import(Position, pm);
    import(Sound, sm);
    import(Text, tm);
    import(Variable, vm);

    {
        Image* new_elem(new Image());

        new_elem->res_data.size = 775;
        im[0] = new_elem;
    }

    {
        Image* new_elem(new Image());

        new_elem->res_data.size = 871;
        im[1] = new_elem;
    }

    set_name("debug game project");
    set_author("benoit guina");
    m_meta.player.x = 0;
    m_meta.player.y = 0;
    m_meta.player.image.id = 1;
    m_meta.player.image.at_x = 0;
    m_meta.player.image.at_y = 0;

    int map_height((int)ProjectManagerBase::map_height);
    int map_width((int)ProjectManagerBase::map_width);
    //int map_height(1);
    //int map_width(1);
    for (int y = 0; y < map_height; ++y)
    {
        for (int x = 0; x < map_width; ++x)
        {
            Position* new_elem(new Position());

            new_elem->res_data.x = x;
            new_elem->res_data.y = y;
            //new_elem->res_data.id_event = 0;
            new_elem->res_data.id_event = -1;
            new_elem->res_data.id_image = 0;
            new_elem->res_data.image_tile_at[0] = 0;
            new_elem->res_data.image_tile_at[1] = 0;
            pm[y * ProjectManagerBase::map_width + x] = new_elem;
        }
    }

    {
        //Event* e = new Event;
        //em[0] = new ;
    }

    debug("debug map created\n");

    load();
}
