#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.gresource"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[5356]; const double alignment; void * const ptr;}  gresource_resource_data = { {
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
  0xd0, 0x04, 0x00, 0x00, 0xdf, 0x14, 0x00, 0x00, 
  0x4b, 0x50, 0x90, 0x0b, 0x01, 0x00, 0x00, 0x00, 
  0xdf, 0x14, 0x00, 0x00, 0x04, 0x00, 0x4c, 0x00, 
  0xe4, 0x14, 0x00, 0x00, 0xec, 0x14, 0x00, 0x00, 
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
  0x8b, 0x5e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x78, 0xda, 0xed, 0x5c, 0xcd, 0x6e, 0xe3, 0x36, 
  0x10, 0xbe, 0xef, 0x53, 0xa8, 0x3a, 0xb5, 0x28, 
  0xb4, 0x89, 0xb3, 0xdb, 0x45, 0x0f, 0x89, 0x8b, 
  0x6e, 0xb7, 0x29, 0x02, 0x74, 0x81, 0x02, 0xbb, 
  0x6d, 0x8f, 0x02, 0x25, 0x8d, 0x25, 0x36, 0x14, 
  0xa9, 0x92, 0x94, 0x1d, 0xf7, 0x05, 0xfa, 0x06, 
  0x7d, 0x94, 0x5e, 0xfa, 0x3a, 0x45, 0x9f, 0xa3, 
  0x43, 0xca, 0xde, 0xd8, 0x89, 0x24, 0x9b, 0x92, 
  0xff, 0x12, 0xfb, 0xb0, 0x8b, 0x58, 0xe2, 0x50, 
  0x9c, 0xe1, 0x37, 0xc3, 0xe1, 0x70, 0x86, 0x97, 
  0xdf, 0xdc, 0xe5, 0xcc, 0x1b, 0x83, 0x54, 0x54, 
  0xf0, 0x2b, 0x7f, 0xf0, 0xf2, 0xdc, 0xf7, 0x80, 
  0xc7, 0x22, 0xa1, 0x3c, 0xbd, 0xf2, 0x7f, 0xfe, 
  0x78, 0x1d, 0x7c, 0xed, 0x7f, 0x33, 0x7c, 0x71, 
  0xf9, 0x59, 0x10, 0x78, 0x3f, 0x00, 0x07, 0x49, 
  0x34, 0x24, 0xde, 0x84, 0xea, 0xcc, 0x4b, 0x19, 
  0x49, 0xc0, 0x7b, 0xf5, 0xf2, 0xe2, 0xe2, 0xe5, 
  0xc0, 0x0b, 0x02, 0x6c, 0x44, 0xb9, 0x06, 0x39, 
  0x22, 0x31, 0x0c, 0x5f, 0x78, 0xde, 0xa5, 0x84, 
  0xdf, 0x4b, 0x2a, 0x41, 0x79, 0x8c, 0x46, 0x57, 
  0x7e, 0xaa, 0x6f, 0xbf, 0xf4, 0xef, 0x3f, 0x84, 
  0x64, 0xe7, 0xfe, 0x99, 0x6d, 0x27, 0xa2, 0xdf, 
  0x20, 0xd6, 0x5e, 0xcc, 0x88, 0x52, 0x57, 0xfe, 
  0x0f, 0xfa, 0xf6, 0x26, 0x27, 0x29, 0xf8, 0x1e, 
  0x4d, 0xae, 0x7c, 0xe0, 0x89, 0x6f, 0x1a, 0x61, 
  0xb3, 0x42, 0x8a, 0x02, 0xa4, 0x9e, 0x7a, 0x9c, 
  0xe4, 0x70, 0xe5, 0x8f, 0xa9, 0xa2, 0x11, 0x03, 
  0x7f, 0xf8, 0x51, 0x96, 0x70, 0x79, 0x36, 0x7f, 
  0x5b, 0xdf, 0x38, 0x26, 0x3c, 0x1c, 0x89, 0xb8, 
  0x54, 0xfe, 0xf0, 0x9a, 0x30, 0xb5, 0xb2, 0x3d, 
  0x8d, 0x05, 0x0f, 0xcd, 0x9f, 0xfe, 0x30, 0x15, 
  0x01, 0x0e, 0x4c, 0x07, 0x6a, 0x9a, 0x47, 0x82, 
  0xd1, 0x78, 0x99, 0xf4, 0xf2, 0xac, 0x1a, 0xfd, 
  0x3a, 0x8c, 0x0c, 0xf6, 0xcf, 0xc9, 0x88, 0xca, 
  0xfe, 0xac, 0x14, 0xa4, 0x54, 0xb0, 0x67, 0x5e, 
  0x72, 0x48, 0x28, 0x09, 0x0a, 0x46, 0xa6, 0x11, 
  0x89, 0x6f, 0x03, 0x3b, 0xa4, 0xde, 0x7c, 0x65, 
  0x42, 0x8b, 0x3d, 0xf3, 0x15, 0xe3, 0xff, 0x12, 
  0x19, 0x33, 0x43, 0xd9, 0x08, 0x3f, 0x6a, 0xcf, 
  0x0c, 0x91, 0xa2, 0x60, 0xa0, 0x55, 0xa0, 0x62, 
  0x09, 0xc0, 0x55, 0x26, 0x04, 0x9a, 0x88, 0xde, 
  0x9c, 0xe1, 0xbc, 0x1f, 0x16, 0x00, 0x95, 0x26, 
  0xb2, 0x9b, 0x62, 0x7d, 0x9b, 0xfc, 0x56, 0x2a, 
  0x9d, 0x03, 0xd7, 0x33, 0xde, 0xa4, 0x48, 0xd1, 
  0x68, 0x36, 0xcd, 0x5b, 0x59, 0xe0, 0x2f, 0x7f, 
  0x38, 0x38, 0x3f, 0x5f, 0x35, 0x58, 0xa5, 0xa1, 
  0x08, 0x29, 0x47, 0xb9, 0xdb, 0xce, 0x87, 0x83, 
  0x55, 0x04, 0x05, 0xca, 0x77, 0x89, 0xe0, 0xbc, 
  0x0f, 0x1f, 0x63, 0xc1, 0xca, 0x1c, 0x7a, 0x73, 
  0x31, 0x26, 0xac, 0x84, 0x03, 0xe0, 0x57, 0x43, 
  0x8e, 0x93, 0xad, 0x61, 0xce, 0xf1, 0xfb, 0xe9, 
  0x7b, 0x42, 0xf9, 0xaf, 0x94, 0xfb, 0x5e, 0x41, 
  0x24, 0xd2, 0x5b, 0x21, 0xe0, 0xef, 0x44, 0x4c, 
  0x1a, 0x98, 0x9e, 0xd0, 0x44, 0x67, 0xa1, 0x59, 
  0x15, 0x41, 0xe1, 0xe7, 0xde, 0xbc, 0x5e, 0xc9, 
  0x52, 0x06, 0x34, 0xcd, 0xf4, 0x3d, 0xc9, 0xeb, 
  0xaf, 0xcf, 0x7b, 0x43, 0x5a, 0xd1, 0x94, 0x13, 
  0x36, 0x6b, 0x9d, 0x00, 0x2a, 0x27, 0x04, 0x30, 
  0xb6, 0xd3, 0x96, 0x11, 0x9e, 0x30, 0x90, 0x76, 
  0xad, 0x0e, 0x73, 0x64, 0x2f, 0xc4, 0x05, 0x1c, 
  0x9f, 0xab, 0x09, 0x6a, 0x31, 0xe0, 0x9c, 0x72, 
  0x51, 0x2d, 0xd9, 0xd8, 0x4d, 0x9c, 0x51, 0x96, 
  0x54, 0x7f, 0x9b, 0x41, 0x30, 0x5c, 0xf4, 0x33, 
  0xc1, 0x12, 0x90, 0xf3, 0x06, 0x67, 0x0b, 0x2d, 
  0x1e, 0xb4, 0x7e, 0x84, 0x9d, 0xb7, 0xe2, 0xce, 
  0x9f, 0xbf, 0x75, 0x54, 0xe9, 0x2e, 0x32, 0xa8, 
  0xa3, 0x11, 0x92, 0xa2, 0x0c, 0x88, 0x46, 0xe7, 
  0xc4, 0x1f, 0xa2, 0x97, 0xa2, 0x69, 0x4c, 0x58, 
  0x2d, 0xe1, 0x12, 0x2f, 0xf5, 0xfc, 0xbc, 0x07, 
  0x5e, 0xbe, 0x25, 0xd2, 0x5f, 0x6c, 0xd5, 0x81, 
  0xaf, 0xae, 0xbc, 0xd5, 0x0f, 0xb3, 0x79, 0xa8, 
  0x37, 0x08, 0x6e, 0xff, 0x61, 0xd3, 0x8e, 0xe3, 
  0xed, 0x33, 0xe6, 0x3a, 0x5a, 0x46, 0x22, 0x60, 
  0xbe, 0xa7, 0x25, 0xe1, 0x0a, 0xf5, 0x8f, 0xe0, 
  0x00, 0xae, 0xfc, 0x29, 0x60, 0x57, 0xff, 0xfd, 
  0xf5, 0xe7, 0xbf, 0xff, 0xfc, 0xfd, 0x79, 0x78, 
  0xfd, 0x85, 0x4b, 0x7f, 0xe8, 0x27, 0x84, 0x25, 
  0x47, 0x9c, 0x32, 0xca, 0xd7, 0x61, 0xc5, 0x8a, 
  0xd1, 0xd3, 0xd3, 0xc2, 0x58, 0x98, 0x32, 0x42, 
  0x4b, 0x51, 0xd6, 0x88, 0xaa, 0x49, 0xb2, 0xb5, 
  0x4d, 0x7b, 0x48, 0xb6, 0xaf, 0x74, 0x9b, 0x91, 
  0xd1, 0xcc, 0x87, 0x5d, 0x77, 0x5b, 0x60, 0xd2, 
  0x3e, 0x73, 0x43, 0xb4, 0x25, 0x01, 0x87, 0xc9, 
  0xaa, 0x51, 0xf5, 0x16, 0xcb, 0x26, 0x44, 0xb3, 
  0x01, 0xc0, 0xb4, 0x75, 0xa3, 0xb4, 0x88, 0x6f, 
  0x1d, 0xba, 0x58, 0x32, 0xd5, 0x24, 0xd6, 0x74, 
  0x8c, 0x0b, 0xd0, 0x82, 0x99, 0xce, 0xa7, 0x95, 
  0x95, 0x9e, 0xe0, 0xbf, 0x10, 0x65, 0xec, 0x7b, 
  0xd5, 0xe4, 0x2d, 0xad, 0x4e, 0x35, 0xc6, 0xbb, 
  0xe6, 0x53, 0x0b, 0x4b, 0x5d, 0xdd, 0xdb, 0x16, 
  0xc8, 0xec, 0x01, 0x4e, 0xf8, 0x9c, 0x9f, 0xf0, 
  0xb4, 0x5d, 0x3c, 0x19, 0x19, 0x1f, 0x0b, 0x9e, 
  0x14, 0x19, 0xc3, 0x09, 0x4f, 0xdb, 0xc5, 0x93, 
  0x91, 0xf1, 0x31, 0xe1, 0x29, 0x20, 0xea, 0x04, 
  0xa9, 0xed, 0x43, 0x2a, 0x24, 0xea, 0x58, 0x50, 
  0x55, 0x48, 0x18, 0x01, 0xee, 0x34, 0x63, 0x38, 
  0x21, 0x6b, 0x0b, 0xc8, 0x32, 0x7b, 0x5e, 0xdc, 
  0xa1, 0xa7, 0xa0, 0x43, 0x95, 0x89, 0x05, 0x5f, 
  0x4a, 0xe1, 0x93, 0x84, 0x12, 0x26, 0xd2, 0x05, 
  0x58, 0x99, 0x1d, 0xc8, 0x21, 0xe0, 0xea, 0x03, 
  0x14, 0x44, 0x12, 0x2d, 0x64, 0x07, 0x6c, 0xed, 
  0x01, 0x11, 0x4f, 0x4b, 0xe3, 0x4c, 0xf4, 0xe3, 
  0xa4, 0x6a, 0xdb, 0x51, 0xb5, 0xf6, 0xf0, 0xd2, 
  0x06, 0x91, 0xd3, 0x4c, 0xd8, 0x40, 0x54, 0x4f, 
  0x50, 0xd3, 0xb8, 0xae, 0xe1, 0x65, 0x41, 0xe2, 
  0x5b, 0xca, 0xd3, 0xf6, 0x20, 0x0e, 0xdc, 0x15, 
  0xc4, 0x1c, 0x6c, 0xb5, 0x47, 0x70, 0x1e, 0x10, 
  0x8d, 0x28, 0x63, 0x6e, 0xb1, 0xa2, 0x42, 0x28, 
  0x5a, 0x05, 0xb4, 0xce, 0xeb, 0x49, 0xf0, 0xe9, 
  0xc3, 0xe1, 0x3e, 0xe2, 0x73, 0x9d, 0x78, 0xd7, 
  0x0d, 0x1f, 0x09, 0x13, 0xef, 0xb2, 0x81, 0x5f, 
  0x8a, 0x3f, 0xc2, 0x68, 0xcf, 0xd1, 0xaf, 0x07, 
  0x74, 0x12, 0xc6, 0x40, 0x18, 0x24, 0x6b, 0x05, 
  0xcd, 0x3c, 0x7b, 0x8c, 0x89, 0x08, 0x0e, 0xec, 
  0xcf, 0x0a, 0xc2, 0x82, 0x87, 0x44, 0x02, 0xf1, 
  0x57, 0x47, 0xd4, 0xde, 0x96, 0x5a, 0x0b, 0xbe, 
  0x1c, 0xd2, 0xdc, 0x46, 0x64, 0x4c, 0xe1, 0xdc, 
  0xe1, 0xd4, 0xf9, 0xc3, 0x37, 0x6e, 0xf1, 0xb4, 
  0xa9, 0x28, 0x71, 0x89, 0xd3, 0x53, 0x23, 0x7b, 
  0xe0, 0xc9, 0xea, 0xe8, 0x57, 0xad, 0x56, 0x3d, 
  0x8e, 0xf8, 0x76, 0x56, 0xad, 0x26, 0xad, 0xe9, 
  0xac, 0x39, 0xcd, 0xda, 0xe3, 0x4c, 0xb6, 0x52, 
  0x85, 0x1a, 0xd4, 0xa8, 0x51, 0x08, 0x0d, 0x10, 
  0x8b, 0x05, 0x3e, 0xe0, 0x7a, 0x6d, 0x8c, 0xed, 
  0x0e, 0x5d, 0x83, 0x37, 0x1d, 0x11, 0xf2, 0x68, 
  0xd0, 0x3f, 0x56, 0xa1, 0xdc, 0x4f, 0x36, 0x22, 
  0x07, 0xa5, 0xcc, 0x91, 0xde, 0x21, 0xc6, 0x48, 
  0xd7, 0x8e, 0x42, 0xbf, 0xaf, 0x98, 0x68, 0xef, 
  0xb0, 0x6d, 0xf1, 0x6a, 0xc6, 0x7e, 0x2f, 0xfc, 
  0x77, 0x5b, 0x41, 0x7a, 0xa9, 0x41, 0x8b, 0x2a, 
  0x9c, 0x6c, 0xc2, 0xb3, 0x70, 0x23, 0x06, 0xdb, 
  0x75, 0x23, 0xde, 0x49, 0x82, 0xfb, 0xfa, 0xf4, 
  0x5b, 0x63, 0x03, 0xad, 0x99, 0x98, 0x59, 0xc5, 
  0xbd, 0x7a, 0x12, 0xcb, 0xe7, 0xa5, 0x38, 0xc2, 
  0x05, 0x47, 0x76, 0x6e, 0xb5, 0xcd, 0xe3, 0x30, 
  0x8e, 0xdc, 0x22, 0x11, 0xfd, 0xe7, 0xdd, 0x85, 
  0xdf, 0x3e, 0xd3, 0x7e, 0xb1, 0xdd, 0x69, 0xff, 
  0x10, 0x4b, 0xc1, 0x58, 0x34, 0xf7, 0x1f, 0xc7, 
  0x34, 0x01, 0x11, 0x3e, 0x48, 0x83, 0x38, 0x08, 
  0x2f, 0x92, 0xdc, 0xa7, 0x38, 0x0c, 0xe7, 0xe3, 
  0x5b, 0x0f, 0x37, 0x31, 0x42, 0x26, 0x85, 0xa0, 
  0x4a, 0x66, 0xb8, 0xc7, 0xcf, 0x32, 0xab, 0x61, 
  0xd5, 0x2a, 0xb4, 0xad, 0xf6, 0x00, 0xa7, 0x9d, 
  0x99, 0x91, 0x57, 0xdb, 0xc5, 0x53, 0x93, 0x03, 
  0xbe, 0x57, 0xec, 0x64, 0x22, 0x17, 0x29, 0x70, 
  0x10, 0x86, 0xd2, 0xe5, 0x83, 0xcb, 0x0e, 0xbb, 
  0xcd, 0x33, 0xea, 0x7b, 0xe6, 0x5f, 0x09, 0x68, 
  0x47, 0x27, 0xfe, 0xae, 0xa4, 0x12, 0x62, 0xa0, 
  0x63, 0x50, 0x61, 0x02, 0x23, 0x52, 0x32, 0xed, 
  0xde, 0x03, 0xb5, 0x89, 0x62, 0x66, 0x6f, 0x33, 
  0x70, 0xfb, 0x30, 0xa3, 0x30, 0xf2, 0x87, 0x5c, 
  0x70, 0xa7, 0xcf, 0x11, 0x36, 0x21, 0x53, 0x65, 
  0x83, 0x86, 0xe1, 0xec, 0xd3, 0x2b, 0x47, 0xbc, 
  0x6c, 0x1c, 0x18, 0x8d, 0x6f, 0x71, 0x6f, 0x5a, 
  0x1f, 0xe5, 0x2e, 0x70, 0xef, 0xea, 0x6c, 0x0c, 
  0x36, 0xeb, 0x58, 0xb9, 0x4e, 0xc0, 0x7a, 0x7e, 
  0xe6, 0x8e, 0xb6, 0x5a, 0x27, 0x75, 0xa8, 0x30, 
  0x69, 0x52, 0x15, 0x9f, 0x83, 0x3a, 0x20, 0x1b, 
  0x47, 0xa6, 0x0e, 0x83, 0x93, 0x3a, 0x6c, 0x41, 
  0x1d, 0x4c, 0xc6, 0xf8, 0x73, 0xd0, 0x07, 0xc3, 
  0xc7, 0x91, 0x29, 0xc4, 0xc5, 0x49, 0x21, 0xb6, 
  0xe2, 0x2e, 0x3d, 0x03, 0x75, 0xe0, 0x70, 0xa7, 
  0x8f, 0x4c, 0x1b, 0x5e, 0xed, 0x56, 0x1b, 0x7e, 
  0xb1, 0x79, 0xfd, 0x07, 0xad, 0x13, 0x96, 0x2c, 
  0x14, 0x3c, 0xb4, 0x58, 0xe9, 0x10, 0xe1, 0xeb, 
  0xaf, 0x54, 0x5d, 0xd5, 0x63, 0xed, 0x34, 0xf4, 
  0x46, 0x79, 0x37, 0xd6, 0x4b, 0xb4, 0x46, 0xfb, 
  0xe9, 0x1f, 0x48, 0x14, 0xd9, 0x49, 0x75, 0xd2, 
  0xe6, 0x85, 0x88, 0x48, 0x55, 0xf0, 0xe1, 0x64, 
  0x79, 0x62, 0xc1, 0x71, 0x7a, 0x49, 0x99, 0x50, 
  0x11, 0x54, 0xe4, 0x41, 0x5e, 0x6a, 0x48, 0x3e, 
  0x15, 0xd2, 0xbc, 0x58, 0x7a, 0x97, 0xd1, 0x34, 
  0x6b, 0x78, 0xc5, 0xc4, 0xa4, 0xe1, 0x8d, 0x29, 
  0xd4, 0x29, 0xf3, 0x86, 0xd2, 0x9c, 0x36, 0x43, 
  0x63, 0x25, 0x19, 0x54, 0x31, 0x99, 0x45, 0x73, 
  0x53, 0xf5, 0x3b, 0x0b, 0xd6, 0x24, 0x9d, 0x8c, 
  0x4d, 0xe3, 0x31, 0x50, 0xc1, 0x10, 0xb8, 0x51, 
  0x93, 0x6e, 0x39, 0x2d, 0x4e, 0x3d, 0x75, 0x6a, 
  0x33, 0x6a, 0x51, 0x1b, 0x09, 0x21, 0x0c, 0xc5, 
  0xec, 0x0f, 0x63, 0x30, 0xcc, 0xbb, 0x52, 0x8f, 
  0x7b, 0x51, 0xaf, 0xab, 0x96, 0x1d, 0xd2, 0x06, 
  0x1a, 0xe7, 0x34, 0xa7, 0xfc, 0x34, 0xa9, 0x4f, 
  0x74, 0x52, 0x9f, 0xae, 0x57, 0xf0, 0xfa, 0xe4, 
  0x23, 0x6f, 0x61, 0xd3, 0x68, 0x2a, 0x6a, 0x9f, 
  0x81, 0x97, 0xac, 0xc9, 0x2d, 0x84, 0x96, 0x99, 
  0x23, 0xf3, 0x95, 0xbf, 0xda, 0xad, 0x56, 0x7c, 
  0x14, 0x69, 0xca, 0xe6, 0xbe, 0xb2, 0x3d, 0xdc, 
  0xca, 0x4b, 0x16, 0x2e, 0xd6, 0x99, 0x3f, 0x6f, 
  0x55, 0x51, 0x07, 0xa9, 0x2b, 0x4f, 0x17, 0xbe, 
  0x6f, 0x8e, 0x23, 0xdf, 0x00, 0xc7, 0x12, 0x9a, 
  0x8a, 0xcb, 0xd6, 0xa0, 0xc4, 0xde, 0x8e, 0x17, 
  0xbf, 0xb7, 0x52, 0x80, 0xd9, 0x69, 0xb5, 0x2a, 
  0x23, 0x4d, 0x35, 0x83, 0x50, 0x4b, 0x12, 0xc3, 
  0x96, 0x4f, 0x1c, 0xdd, 0xce, 0x0d, 0x23, 0x60, 
  0xa1, 0xbb, 0xf4, 0x25, 0x98, 0xcd, 0x60, 0xa8, 
  0x45, 0xc1, 0x60, 0x0c, 0xab, 0x88, 0xeb, 0x0d, 
  0x61, 0x73, 0x72, 0x60, 0x5b, 0x4e, 0x5c, 0x55, 
  0x64, 0x3b, 0xcb, 0xbf, 0x5e, 0x69, 0x5b, 0x7f, 
  0xac, 0x6d, 0x77, 0xf0, 0x55, 0xcb, 0x73, 0xbc, 
  0x78, 0x16, 0x2f, 0xae, 0x46, 0xea, 0x69, 0xa7, 
  0x0f, 0xbd, 0xee, 0xaa, 0x98, 0xcb, 0x3c, 0x2e, 
  0xbc, 0xbc, 0x3c, 0x9b, 0xdf, 0xcb, 0x50, 0x7f, 
  0x29, 0xc5, 0xbb, 0x59, 0xdd, 0x86, 0xd5, 0xd4, 
  0xfb, 0x3a, 0x8e, 0xcd, 0xdc, 0x06, 0x62, 0xf0, 
  0x1a, 0x66, 0xd4, 0xc4, 0x3e, 0xaa, 0x7e, 0x57, 
  0x11, 0xd8, 0xdb, 0x16, 0x88, 0x05, 0xe3, 0x7a, 
  0x1f, 0x30, 0xf0, 0x31, 0xf1, 0x20, 0x1c, 0x96, 
  0xf4, 0x87, 0x9f, 0xdc, 0xb3, 0x55, 0x74, 0x44, 
  0x6b, 0x12, 0x67, 0x90, 0x84, 0xc6, 0xcd, 0x68, 
  0xa6, 0x7a, 0xe0, 0x30, 0x0a, 0xd5, 0x50, 0x0e, 
  0x93, 0xd1, 0x04, 0x36, 0x76, 0x09, 0xc4, 0xa3, 
  0xed, 0xf1, 0x38, 0x5a, 0x48, 0xd4, 0x70, 0xbd, 
  0x1a, 0x62, 0xbb, 0x37, 0x3d, 0x34, 0xa5, 0xc4, 
  0x5e, 0x34, 0xdf, 0x0b, 0xb1, 0x76, 0xee, 0x78, 
  0xf7, 0xb4, 0x95, 0xae, 0x19, 0x28, 0x6b, 0x67, 
  0x7e, 0x6f, 0x7c, 0xcf, 0xb7, 0x50, 0x52, 0x63, 
  0x61, 0xe6, 0x14, 0xcf, 0x7c, 0x92, 0x4e, 0xb0, 
  0x43, 0xd5, 0xcc, 0x0e, 0xb6, 0x7e, 0x8f, 0x74, 
  0xd9, 0xbd, 0xb4, 0xed, 0xc8, 0x93, 0x49, 0xf6, 
  0xb2, 0xc8, 0x3a, 0x91, 0xec, 0xac, 0xd6, 0xe7, 
  0xc0, 0xf2, 0xea, 0x9c, 0x0e, 0x4c, 0xd6, 0xb5, 
  0x6c, 0xd7, 0x92, 0xe4, 0x70, 0xa8, 0xbe, 0xa5, 
  0x16, 0x82, 0x69, 0x5a, 0x84, 0x1a, 0xee, 0x74, 
  0xad, 0x8b, 0x79, 0x33, 0xf2, 0x74, 0x06, 0x9e, 
  0x2a, 0x20, 0x46, 0xdd, 0xf6, 0x12, 0x8a, 0xf6, 
  0x4c, 0x0b, 0x39, 0xf5, 0xa8, 0xc2, 0xe5, 0xc9, 
  0xc4, 0x5a, 0x13, 0xef, 0xc5, 0x8d, 0xf6, 0x26, 
  0x88, 0x32, 0x2f, 0xc2, 0x86, 0x64, 0x0c, 0xe8, 
  0x7d, 0x0b, 0x2f, 0x13, 0x39, 0x9c, 0xd9, 0x8d, 
  0xfb, 0x3d, 0x91, 0xb3, 0xd7, 0x1b, 0xde, 0xcd, 
  0x82, 0xb9, 0x6e, 0x07, 0x50, 0x19, 0x49, 0xd0, 
  0xe0, 0x55, 0xbb, 0x3e, 0xca, 0x37, 0x55, 0x72, 
  0x52, 0x5f, 0x27, 0x73, 0x70, 0xe5, 0x25, 0x39, 
  0x91, 0x29, 0xe5, 0x21, 0x83, 0x91, 0x6e, 0x8d, 
  0x51, 0xb5, 0x52, 0x4b, 0x73, 0x57, 0x58, 0x77, 
  0x72, 0xdc, 0xf0, 0x75, 0x27, 0x8e, 0x04, 0xba, 
  0x02, 0x79, 0x07, 0x7a, 0xe7, 0xf3, 0xce, 0x2e, 
  0xa5, 0xc0, 0xdf, 0x65, 0x10, 0xdf, 0x2e, 0x46, 
  0xe1, 0xaa, 0xd0, 0xe7, 0xec, 0xfe, 0x80, 0xb0, 
  0xca, 0xc2, 0x46, 0xc4, 0x3b, 0x57, 0x09, 0xd7, 
  0x69, 0xdf, 0x07, 0x7c, 0xef, 0x11, 0xe5, 0xfd, 
  0x62, 0x7a, 0xf5, 0xae, 0x29, 0x6e, 0xf5, 0xde, 
  0xcd, 0x95, 0xe9, 0xe5, 0xbe, 0xab, 0x89, 0xbb, 
  0x76, 0xf1, 0xd8, 0x23, 0xea, 0x5c, 0x97, 0x6c, 
  0xeb, 0x81, 0x7b, 0x70, 0x63, 0x6b, 0x2d, 0x28, 
  0x4f, 0x10, 0x28, 0xda, 0xec, 0x8a, 0xd6, 0xeb, 
  0xa7, 0xbd, 0x7c, 0x78, 0x55, 0x15, 0x56, 0xef, 
  0x4a, 0xac, 0x7e, 0xd5, 0x58, 0xbd, 0x2a, 0xb2, 
  0x56, 0x54, 0x65, 0xad, 0xa8, 0x9e, 0x76, 0x57, 
  0x36, 0x83, 0xf8, 0xef, 0x32, 0x81, 0x6e, 0xbe, 
  0x6c, 0x56, 0xb9, 0xd9, 0xda, 0xe4, 0xa8, 0x74, 
  0x07, 0x51, 0x57, 0x5f, 0x6d, 0xe8, 0xfc, 0xa1, 
  0xc2, 0xcd, 0x7c, 0xac, 0x83, 0x91, 0xdd, 0xef, 
  0x76, 0xe9, 0xc8, 0x86, 0x81, 0xea, 0x4c, 0xc8, 
  0xd9, 0x11, 0x82, 0x78, 0xb0, 0x4d, 0x10, 0x77, 
  0x3f, 0xcb, 0x6f, 0x0b, 0x49, 0xba, 0x85, 0x25, 
  0x9f, 0x50, 0x49, 0xeb, 0x4f, 0xd6, 0x03, 0xfc, 
  0x40, 0xc6, 0x28, 0xeb, 0xfb, 0xb5, 0xeb, 0x60, 
  0x4f, 0xd6, 0x3b, 0x96, 0x7d, 0x3e, 0xf9, 0x1d, 
  0xe5, 0xae, 0xaa, 0xff, 0x06, 0x5b, 0x88, 0xda, 
  0xce, 0x5f, 0x5c, 0x9e, 0x2d, 0x5c, 0x19, 0xff, 
  0x3f, 0x86, 0xff, 0x35, 0x56, 0x00, 0x00, 0x00, 
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
