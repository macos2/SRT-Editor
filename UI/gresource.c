#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.gresource"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[3308]; const double alignment; void * const ptr;}  gresource_resource_data = { {
  0x47, 0x56, 0x61, 0x72, 0x69, 0x61, 0x6e, 0x74, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x28, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
  0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
  0x98, 0xab, 0x22, 0x18, 0x03, 0x00, 0x00, 0x00, 
  0x90, 0x00, 0x00, 0x00, 0x15, 0x00, 0x76, 0x00, 
  0xa8, 0x00, 0x00, 0x00, 0xb7, 0x04, 0x00, 0x00, 
  0xd4, 0xb5, 0x02, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xb7, 0x04, 0x00, 0x00, 0x01, 0x00, 0x4c, 0x00, 
  0xb8, 0x04, 0x00, 0x00, 0xbc, 0x04, 0x00, 0x00, 
  0xc9, 0x01, 0x63, 0xa2, 0x03, 0x00, 0x00, 0x00, 
  0xbc, 0x04, 0x00, 0x00, 0x0d, 0x00, 0x76, 0x00, 
  0xd0, 0x04, 0x00, 0x00, 0xdf, 0x0c, 0x00, 0x00, 
  0x4b, 0x50, 0x90, 0x0b, 0x01, 0x00, 0x00, 0x00, 
  0xdf, 0x0c, 0x00, 0x00, 0x04, 0x00, 0x4c, 0x00, 
  0xe4, 0x0c, 0x00, 0x00, 0xec, 0x0c, 0x00, 0x00, 
  0x53, 0x75, 0x62, 0x54, 0x69, 0x74, 0x6c, 0x65, 
  0x44, 0x69, 0x73, 0x70, 0x6c, 0x61, 0x79, 0x2e, 
  0x67, 0x6c, 0x61, 0x64, 0x65, 0x00, 0x00, 0x00, 
  0xf4, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x78, 0xda, 0xed, 0x98, 0x4d, 0x8f, 0x9b, 0x30, 
  0x10, 0x86, 0xef, 0xfb, 0x2b, 0x5c, 0x5f, 0x2b, 
  0x42, 0x92, 0x55, 0xab, 0x1e, 0x80, 0x55, 0x57, 
  0xdb, 0x5d, 0xf5, 0xd0, 0xd3, 0xa6, 0x67, 0x64, 
  0x60, 0x02, 0x6e, 0x8c, 0x4d, 0xed, 0x21, 0x09, 
  0xff, 0xbe, 0x26, 0x1f, 0xca, 0x17, 0x4b, 0x20, 
  0x52, 0xd4, 0x36, 0xed, 0x0d, 0x89, 0x79, 0xf1, 
  0xbc, 0x9e, 0x67, 0xc0, 0x83, 0xf7, 0xb0, 0xcc, 
  0x05, 0x99, 0x83, 0x36, 0x5c, 0x49, 0x9f, 0x8e, 
  0x06, 0x43, 0x4a, 0x40, 0xc6, 0x2a, 0xe1, 0x32, 
  0xf5, 0xe9, 0xf7, 0xc9, 0xb3, 0xf3, 0x89, 0x3e, 
  0x04, 0x77, 0xde, 0x3b, 0xc7, 0x21, 0x2f, 0x20, 
  0x41, 0x33, 0x84, 0x84, 0x2c, 0x38, 0x66, 0x24, 
  0x15, 0x2c, 0x01, 0x72, 0x3f, 0x18, 0x8f, 0x07, 
  0x23, 0xe2, 0x38, 0x36, 0x88, 0x4b, 0x04, 0x3d, 
  0x65, 0x31, 0x04, 0x77, 0x84, 0x78, 0x1a, 0x7e, 
  0x96, 0x5c, 0x83, 0x21, 0x82, 0x47, 0x3e, 0x4d, 
  0x71, 0xf6, 0x9e, 0xee, 0x16, 0xb2, 0xb2, 0x21, 
  0x75, 0x57, 0x71, 0x2a, 0xfa, 0x01, 0x31, 0x92, 
  0x58, 0x30, 0x63, 0x7c, 0xfa, 0x82, 0xb3, 0xaf, 
  0x39, 0x4b, 0x81, 0x12, 0x9e, 0xf8, 0x14, 0x64, 
  0x42, 0xeb, 0x20, 0x1b, 0x56, 0x68, 0x55, 0x80, 
  0xc6, 0x8a, 0x48, 0x96, 0x83, 0x4f, 0xe7, 0xdc, 
  0xf0, 0x48, 0x00, 0x0d, 0x26, 0xba, 0x04, 0xcf, 
  0xdd, 0xde, 0x6d, 0x0e, 0x8e, 0x99, 0x0c, 0xa7, 
  0x2a, 0x2e, 0x0d, 0x0d, 0x9e, 0x99, 0x30, 0x67, 
  0xe3, 0x0d, 0xaa, 0x78, 0x46, 0x03, 0x9b, 0xb3, 
  0x93, 0x2a, 0x54, 0x8e, 0x4d, 0x0d, 0x0f, 0x35, 
  0x9e, 0xbb, 0x4e, 0xfb, 0xac, 0x03, 0x83, 0x4c, 
  0xe3, 0x9f, 0xe0, 0x61, 0xca, 0x75, 0xab, 0x09, 
  0x84, 0xbc, 0x10, 0xb6, 0xba, 0x5b, 0x1b, 0xdf, 
  0xaa, 0xd7, 0x32, 0x9a, 0x70, 0x14, 0xf0, 0xc4, 
  0x8d, 0xbd, 0x53, 0x51, 0x52, 0x30, 0x0d, 0x12, 
  0x57, 0x0e, 0x1f, 0xd5, 0xf2, 0x77, 0x98, 0x52, 
  0x9a, 0xdb, 0x0c, 0x18, 0x5a, 0x86, 0x68, 0x60, 
  0x61, 0x42, 0x1e, 0x33, 0x71, 0x22, 0x8a, 0x33, 
  0x2e, 0x92, 0xf5, 0x75, 0x53, 0x75, 0x1e, 0x4b, 
  0x44, 0x25, 0x77, 0x0e, 0x7a, 0xbb, 0xb8, 0xc4, 
  0x49, 0x63, 0x89, 0x0a, 0x16, 0xdb, 0x3e, 0xa3, 
  0xc1, 0xc7, 0x2e, 0xd1, 0x99, 0xca, 0x55, 0x6a, 
  0x5b, 0x50, 0xd5, 0x6b, 0x74, 0x4d, 0x2b, 0x62, 
  0x06, 0x04, 0x97, 0x10, 0x16, 0xca, 0xf0, 0xf5, 
  0xb6, 0x45, 0xca, 0xda, 0xcf, 0xbb, 0x88, 0x6d, 
  0xd1, 0x55, 0x89, 0xa1, 0xc1, 0xaa, 0xde, 0x09, 
  0xdb, 0x8b, 0x8d, 0xa2, 0x83, 0xdd, 0x6e, 0xdb, 
  0x71, 0xba, 0x1f, 0xd4, 0xb4, 0x5a, 0x04, 0x62, 
  0x0d, 0x2c, 0x24, 0x1c, 0x9b, 0xd6, 0xba, 0xa8, 
  0x52, 0x67, 0xaa, 0xd5, 0x47, 0xa6, 0x21, 0x06, 
  0x3e, 0x07, 0x13, 0x26, 0x30, 0x65, 0xa5, 0xc0, 
  0x7e, 0xea, 0xd2, 0x40, 0xb8, 0xe9, 0xca, 0x3e, 
  0x32, 0x26, 0x16, 0xac, 0x32, 0xa1, 0xc9, 0xd4, 
  0x22, 0xe4, 0xab, 0x17, 0x4b, 0x8b, 0x7c, 0xbf, 
  0xa5, 0x77, 0x0f, 0x64, 0xf1, 0xcc, 0x72, 0xd6, 
  0xbe, 0x0c, 0x2c, 0x0b, 0x56, 0xbf, 0x6d, 0xfb, 
  0xa4, 0x36, 0xe5, 0x42, 0xf4, 0x53, 0xec, 0x30, 
  0x1c, 0xbe, 0x65, 0xe0, 0x24, 0x5b, 0xcf, 0x3d, 
  0x42, 0xec, 0x1a, 0xc8, 0x25, 0x20, 0x00, 0xe1, 
  0x3f, 0x74, 0xb7, 0x0d, 0xdd, 0xe8, 0xba, 0xd0, 
  0x4d, 0x54, 0x9a, 0x0a, 0xe8, 0x81, 0x1e, 0x41, 
  0xcd, 0xa4, 0xb1, 0x9f, 0x5d, 0x66, 0x69, 0xf2, 
  0x69, 0x05, 0x96, 0x8d, 0xd7, 0xfa, 0xc4, 0x70, 
  0x7b, 0x20, 0x6e, 0x28, 0x32, 0x7d, 0xdc, 0xdd, 
  0x28, 0x85, 0xe3, 0xbf, 0x80, 0xc2, 0x2f, 0xcd, 
  0x5f, 0xfb, 0x9b, 0x60, 0x10, 0xba, 0x7b, 0x5b, 
  0x29, 0xf6, 0x0e, 0x4f, 0x9a, 0xa7, 0xd9, 0xbf, 
  0x8e, 0xef, 0xfd, 0xa5, 0xf8, 0x1e, 0x5b, 0x3c, 
  0xb5, 0xf7, 0x96, 0xb5, 0xce, 0x47, 0xea, 0x76, 
  0x5f, 0xbd, 0x4e, 0x23, 0x47, 0x7e, 0x0e, 0xbc, 
  0x9c, 0x1b, 0x31, 0x9e, 0x34, 0x5b, 0x58, 0xe5, 
  0x67, 0x0d, 0x6c, 0x33, 0x06, 0x96, 0x11, 0xd6, 
  0xb3, 0x54, 0xcb, 0xc8, 0x91, 0x41, 0xcd, 0x56, 
  0x58, 0x8f, 0xcd, 0x60, 0x2c, 0xd8, 0x1f, 0x86, 
  0x5d, 0x2c, 0x5c, 0x61, 0x50, 0xb9, 0xbc, 0x4c, 
  0x5d, 0x73, 0xb8, 0xb4, 0x4a, 0xa3, 0x3e, 0x55, 
  0xf2, 0xdc, 0xed, 0x48, 0x1b, 0xdc, 0x79, 0xee, 
  0xde, 0xbf, 0x89, 0x5f, 0x6a, 0xe0, 0x41, 0x86, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x28, 0x75, 0x75, 0x61, 0x79, 0x29, 0x2f, 
  0x03, 0x00, 0x00, 0x00, 0x4d, 0x61, 0x69, 0x6e, 
  0x57, 0x69, 0x6e, 0x2e, 0x67, 0x6c, 0x61, 0x64, 
  0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x21, 0x2e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x78, 0xda, 0xed, 0x5a, 0xc1, 0x6e, 0xe3, 0x36, 
  0x10, 0xbd, 0xe7, 0x2b, 0x54, 0x9e, 0xb6, 0x28, 
  0x14, 0xdb, 0x49, 0x50, 0xec, 0xc1, 0xd6, 0x62, 
  0x83, 0x22, 0x8b, 0x3d, 0xe4, 0xb4, 0xdb, 0xf6, 
  0x28, 0x8c, 0xa5, 0xb1, 0xcc, 0x0d, 0x45, 0xaa, 
  0x24, 0x65, 0xc7, 0xfd, 0x81, 0xfe, 0x41, 0x3f, 
  0xa5, 0x97, 0xfd, 0x9d, 0xa2, 0xdf, 0xd1, 0x91, 
  0x6c, 0x6f, 0x6c, 0x47, 0xb2, 0x2d, 0xc9, 0x4e, 
  0x6c, 0xac, 0x0e, 0x01, 0x22, 0x71, 0x86, 0x9a, 
  0x37, 0xf3, 0x38, 0x63, 0x0e, 0xd9, 0x7f, 0xf7, 
  0x18, 0x0b, 0x67, 0x82, 0xda, 0x70, 0x25, 0x07, 
  0xac, 0x77, 0xd9, 0x65, 0x0e, 0xca, 0x40, 0x85, 
  0x5c, 0x46, 0x03, 0xf6, 0xeb, 0xe7, 0x3b, 0xf7, 
  0x2d, 0x7b, 0xe7, 0x5d, 0xf4, 0x7f, 0x70, 0x5d, 
  0xe7, 0x03, 0x4a, 0xd4, 0x60, 0x31, 0x74, 0xa6, 
  0xdc, 0x8e, 0x9d, 0x48, 0x40, 0x88, 0xce, 0xf5, 
  0xe5, 0xd5, 0xd5, 0x65, 0xcf, 0x71, 0x5d, 0x12, 
  0xe2, 0xd2, 0xa2, 0x1e, 0x41, 0x80, 0xde, 0x85, 
  0xe3, 0xf4, 0x35, 0xfe, 0x91, 0x72, 0x8d, 0xc6, 
  0x11, 0x7c, 0x38, 0x60, 0x91, 0x7d, 0xf8, 0x89, 
  0x3d, 0x7d, 0x88, 0xd4, 0xba, 0xac, 0x93, 0xcb, 
  0xa9, 0xe1, 0x17, 0x0c, 0xac, 0x13, 0x08, 0x30, 
  0x66, 0xc0, 0x3e, 0xd8, 0x87, 0x8f, 0x31, 0x44, 
  0xc8, 0x1c, 0x1e, 0x0e, 0x18, 0xca, 0x90, 0x65, 
  0x42, 0x24, 0x96, 0x68, 0x95, 0xa0, 0xb6, 0x33, 
  0x47, 0x42, 0x8c, 0x03, 0x36, 0xe1, 0x86, 0x0f, 
  0x05, 0x32, 0xef, 0xb3, 0x4e, 0xb1, 0xdf, 0x59, 
  0x8e, 0x16, 0x0b, 0x07, 0x20, 0xfd, 0x91, 0x0a, 
  0x52, 0xc3, 0xbc, 0x3b, 0x10, 0x66, 0xa7, 0xbc, 
  0xb1, 0x2a, 0x78, 0x60, 0x1e, 0xd9, 0xec, 0x46, 
  0xca, 0x2a, 0x97, 0x4c, 0xb3, 0xeb, 0x3a, 0xfd, 
  0xce, 0xdc, 0xec, 0x7d, 0x10, 0xf4, 0x4e, 0x01, 
  0xc2, 0x88, 0xeb, 0xda, 0x18, 0x12, 0x48, 0x0d, 
  0xbe, 0x32, 0x88, 0x18, 0x43, 0x0e, 0x6e, 0x6e, 
  0x49, 0x5d, 0x14, 0x02, 0x66, 0xa7, 0x01, 0x82, 
  0x0c, 0xa9, 0x82, 0xe1, 0x7d, 0xf8, 0x25, 0x35, 
  0x36, 0x46, 0x69, 0x17, 0x40, 0xb4, 0x8a, 0x68, 
  0x5d, 0x99, 0x12, 0x30, 0x69, 0x42, 0x4f, 0xcc, 
  0xeb, 0x75, 0xbb, 0xbb, 0x2d, 0xc3, 0xc4, 0xe7, 
  0x32, 0xd0, 0x98, 0x4f, 0xee, 0xf5, 0x76, 0x29, 
  0x24, 0xe4, 0xcc, 0x35, 0x85, 0xee, 0x16, 0x1c, 
  0x16, 0x63, 0x42, 0x6a, 0x71, 0x89, 0xe4, 0x7e, 
  0x76, 0x0f, 0x5c, 0xfe, 0xce, 0x25, 0x73, 0x12, 
  0xd0, 0xa4, 0x9f, 0x83, 0xa3, 0xe7, 0x50, 0x4d, 
  0x4b, 0xa0, 0x4c, 0x79, 0x68, 0xc7, 0x7e, 0x96, 
  0x48, 0xd0, 0xd0, 0xe7, 0x7e, 0xbe, 0xd9, 0x09, 
  0x69, 0x8c, 0x3c, 0x1a, 0xdb, 0x27, 0x95, 0x9b, 
  0xb7, 0xdd, 0xc6, 0xf1, 0x34, 0x3c, 0x92, 0x20, 
  0x16, 0xd2, 0x21, 0x0a, 0xb4, 0xe8, 0xe2, 0x24, 
  0x0f, 0xc7, 0x18, 0x64, 0x28, 0x50, 0xe7, 0xe9, 
  0xcd, 0x8f, 0x09, 0x9e, 0x4f, 0x39, 0x8f, 0xde, 
  0x9b, 0x29, 0x50, 0x14, 0x28, 0x56, 0x52, 0xcd, 
  0xb3, 0x1c, 0x4d, 0x13, 0x8c, 0xb9, 0x08, 0xe7, 
  0xff, 0x67, 0x46, 0x08, 0xca, 0x93, 0x63, 0x25, 
  0x42, 0xd4, 0x4b, 0x81, 0xce, 0x8a, 0xc4, 0x86, 
  0xf4, 0x33, 0x4e, 0xdc, 0xaa, 0x47, 0xb6, 0x1c, 
  0xad, 0xc8, 0xe7, 0x3a, 0x3e, 0x28, 0xd2, 0x51, 
  0x9a, 0x93, 0x0f, 0xc0, 0x52, 0x3e, 0x67, 0x1e, 
  0x25, 0x76, 0xcb, 0x03, 0x10, 0x85, 0x8a, 0x6b, 
  0x58, 0x8a, 0xf1, 0xdc, 0xa3, 0x4c, 0x6f, 0x41, 
  0xb3, 0x55, 0xa9, 0x1a, 0xb8, 0xea, 0x62, 0x2b, 
  0x36, 0xb3, 0xdc, 0xd4, 0x8f, 0x44, 0x6e, 0xb6, 
  0x29, 0x5a, 0xd3, 0xde, 0x26, 0x36, 0x17, 0xe9, 
  0x0a, 0x18, 0xa2, 0x60, 0x8e, 0xd5, 0x20, 0x0d, 
  0xad, 0x3f, 0x20, 0x03, 0x06, 0x6c, 0x86, 0x34, 
  0xd5, 0x7f, 0x7f, 0xff, 0xf5, 0xef, 0xd7, 0x7f, 
  0xde, 0xf8, 0x77, 0x3f, 0x56, 0x99, 0x8f, 0x32, 
  0xae, 0x9f, 0x4a, 0xe2, 0xa9, 0xe0, 0x72, 0x1f, 
  0x28, 0xb9, 0x1b, 0x1d, 0x3b, 0x4b, 0xb2, 0x0c, 
  0x93, 0x0e, 0x29, 0x53, 0xa4, 0x05, 0xae, 0x2a, 
  0xf3, 0x6c, 0xa1, 0x68, 0x03, 0xcf, 0x36, 0xf5, 
  0x6e, 0x39, 0x33, 0xca, 0x71, 0xe4, 0x45, 0x67, 
  0x0b, 0x4d, 0xb6, 0x47, 0x2e, 0xaf, 0x14, 0x12, 
  0xa7, 0xbb, 0xac, 0x6a, 0xec, 0x96, 0x43, 0xb8, 
  0xe6, 0x00, 0x84, 0xd9, 0x36, 0xcd, 0xa2, 0x76, 
  0xee, 0x3d, 0xc5, 0x5a, 0xaa, 0x86, 0xc0, 0xf2, 
  0x09, 0x15, 0xa0, 0x95, 0x34, 0x1d, 0xcf, 0xe6, 
  0x59, 0x7a, 0x4a, 0x7f, 0x3e, 0xf9, 0x98, 0x39, 
  0xf3, 0xe0, 0xad, 0x55, 0xa7, 0x82, 0xe4, 0x5d, 
  0xf0, 0xa9, 0x95, 0x52, 0x57, 0x34, 0xba, 0x85, 
  0x32, 0xaf, 0x40, 0x27, 0x7a, 0x2f, 0x5b, 0x3e, 
  0x1d, 0x97, 0x4f, 0x99, 0x8f, 0xbf, 0x17, 0x3e, 
  0x19, 0x98, 0x60, 0xcb, 0xa7, 0xe3, 0xf2, 0x29, 
  0xf3, 0xf1, 0xf7, 0xc4, 0x27, 0x17, 0x4c, 0x4b, 
  0xa9, 0xe3, 0x53, 0xca, 0x07, 0x73, 0x16, 0xac, 
  0xfa, 0x84, 0xb4, 0x4b, 0x04, 0xab, 0x74, 0x0d, 
  0x66, 0xbd, 0x02, 0x27, 0xce, 0x6b, 0xbd, 0x65, 
  0xbb, 0xd4, 0x76, 0xb1, 0x1d, 0x7e, 0xb1, 0xed, 
  0x6e, 0x03, 0x1c, 0x90, 0x39, 0xe5, 0x8a, 0x25, 
  0x4a, 0xc5, 0x0a, 0x05, 0xc2, 0x45, 0x82, 0xfd, 
  0x04, 0x82, 0x07, 0x2e, 0xa3, 0xed, 0x9b, 0x6d, 
  0x7c, 0x4c, 0x20, 0xeb, 0xd9, 0x6e, 0xdf, 0x69, 
  0x6f, 0x28, 0x8d, 0xb8, 0x10, 0xd5, 0xf6, 0xf4, 
  0x89, 0x32, 0x7c, 0xde, 0x78, 0xe8, 0x16, 0xab, 
  0xd0, 0xdb, 0x4d, 0x73, 0x9f, 0xe1, 0xdc, 0xa7, 
  0x2f, 0xf1, 0x8b, 0x06, 0x4a, 0x9c, 0xd1, 0x7b, 
  0x8d, 0x30, 0x6f, 0xbe, 0x05, 0x4a, 0xda, 0xbc, 
  0xf7, 0xf5, 0x8a, 0x8d, 0x8a, 0xf5, 0x86, 0x14, 
  0x59, 0xb8, 0xc2, 0xc0, 0x85, 0x7d, 0x7e, 0xf6, 
  0xda, 0x0f, 0x86, 0xd5, 0x52, 0x7d, 0xf3, 0xb8, 
  0x57, 0xc1, 0xdb, 0x24, 0xec, 0xbd, 0xe3, 0x86, 
  0xfd, 0x36, 0xb5, 0x56, 0xc9, 0xf5, 0x26, 0xdb, 
  0xcb, 0xc7, 0x79, 0xb3, 0xb7, 0xa9, 0x62, 0x15, 
  0xa1, 0x44, 0x95, 0x69, 0x56, 0xf9, 0xa0, 0x80, 
  0x99, 0x4a, 0x2d, 0x25, 0xbb, 0x59, 0x66, 0xaa, 
  0xb1, 0xa0, 0x6d, 0xd3, 0x26, 0xd8, 0xdc, 0x41, 
  0x2f, 0xd4, 0x02, 0xab, 0xaa, 0xaa, 0x31, 0x40, 
  0x3e, 0x41, 0xe3, 0x87, 0x38, 0x82, 0x54, 0xd8, 
  0xea, 0x33, 0xf0, 0xfc, 0xd8, 0xc0, 0xcb, 0x0e, 
  0x6f, 0xaa, 0xa8, 0x81, 0x98, 0xc2, 0xcc, 0xf8, 
  0x66, 0xac, 0xa6, 0xfe, 0x62, 0x8a, 0xed, 0x5f, 
  0x2e, 0x4b, 0xe1, 0xc5, 0x8b, 0xae, 0xee, 0xc2, 
  0xab, 0xb7, 0xf8, 0x6a, 0xe5, 0xdd, 0x92, 0x45, 
  0x58, 0x5a, 0x94, 0x5a, 0xbe, 0xad, 0xf2, 0xed, 
  0xf9, 0xc9, 0x50, 0xcb, 0xb7, 0xed, 0x09, 0xbf, 
  0xe5, 0x5b, 0x23, 0xbe, 0x3d, 0x3f, 0x4e, 0x6d, 
  0x09, 0xb7, 0x20, 0xdc, 0x55, 0x4b, 0xb8, 0xa3, 
  0x14, 0xd4, 0x96, 0x6e, 0x85, 0x74, 0xbb, 0x7e, 
  0x59, 0xba, 0xfd, 0xa6, 0x44, 0x1a, 0xe3, 0x49, 
  0x93, 0x2e, 0x57, 0xf3, 0x95, 0xf4, 0x03, 0xc1, 
  0xb3, 0x4d, 0x7a, 0xe5, 0x83, 0xd0, 0xe6, 0xac, 
  0xd5, 0x28, 0x38, 0x8e, 0x98, 0x27, 0x95, 0xac, 
  0xa4, 0xb7, 0xf7, 0xd1, 0x78, 0xd9, 0x04, 0x86, 
  0xff, 0x49, 0xce, 0x16, 0xa0, 0x23, 0x74, 0xad, 
  0x52, 0x62, 0x08, 0xba, 0xd2, 0x6a, 0xa3, 0x5d, 
  0x20, 0x79, 0x1c, 0xd2, 0x90, 0x2b, 0x77, 0x92, 
  0x87, 0xda, 0x8d, 0x53, 0x8b, 0xa1, 0x6b, 0x66, 
  0xf1, 0x50, 0x91, 0x3f, 0x2f, 0xd6, 0xc6, 0xc6, 
  0x3c, 0x1a, 0x97, 0x0c, 0x09, 0x35, 0x2d, 0x19, 
  0xc9, 0x2e, 0xb3, 0xa4, 0xf1, 0xb7, 0xc1, 0x3d, 
  0xce, 0x84, 0xf3, 0xfb, 0x61, 0xb4, 0x73, 0x75, 
  0xf3, 0xc7, 0xec, 0x46, 0x0e, 0x05, 0x78, 0x58, 
  0xc6, 0xc1, 0x4a, 0x59, 0xb2, 0x21, 0xf7, 0x0e, 
  0x43, 0x9f, 0xc2, 0x4d, 0x1b, 0x08, 0xda, 0xad, 
  0x33, 0x2f, 0xc0, 0x0c, 0x7c, 0x55, 0xed, 0x49, 
  0x23, 0xed, 0x7d, 0xe9, 0x5b, 0xa3, 0x95, 0x54, 
  0x1a, 0xd3, 0x98, 0xcb, 0x36, 0xa8, 0x67, 0x1a, 
  0xd4, 0xf3, 0xad, 0x9e, 0x37, 0x87, 0xa8, 0x9e, 
  0xa7, 0xdf, 0xf5, 0x24, 0x5b, 0xfc, 0xec, 0x62, 
  0xcd, 0xd6, 0x1f, 0x52, 0x95, 0x7f, 0xd2, 0x1e, 
  0xaa, 0x69, 0xf6, 0x29, 0xd0, 0x4a, 0x64, 0xa5, 
  0xea, 0x94, 0x9a, 0x66, 0xf0, 0x74, 0x79, 0xd2, 
  0x5b, 0x5e, 0x9c, 0x2c, 0x73, 0xc3, 0xd9, 0x34, 
  0xbd, 0xaf, 0xeb, 0x06, 0x72, 0x1d, 0xe3, 0xca, 
  0x60, 0xbf, 0xb3, 0xbc, 0xae, 0xe9, 0x5d, 0xf4, 
  0x3b, 0x2b, 0x17, 0xb9, 0xff, 0x07, 0x48, 0xc6, 
  0x3c, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x28, 0x75, 0x75, 0x61, 0x79, 0x29, 0x6f, 
  0x72, 0x67, 0x2f, 0x00, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
} };

static GStaticResource static_resource = { gresource_resource_data.data, sizeof (gresource_resource_data.data), NULL, NULL, NULL };
extern GResource *gresource_get_resource (void);
GResource *gresource_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a sane way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for Win32 (x86) and x64 programs, as symbols on Win32 are prefixed
 * with an underscore but symbols on x64 are not.
 */
#ifdef _WIN64
#define G_MSVC_SYMBOL_PREFIX ""
#else
#define G_MSVC_SYMBOL_PREFIX "_"
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
