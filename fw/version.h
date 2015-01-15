#ifndef _VERSION_H_
#define _VERSION_H_

#define XAT_MAJOR	0
#define XAT_MINOR	1
#define XAT_PATCH	0

//#define GIT_DESC	"$(shell git describe)"

#define FREEZE_WSTR(s)	L ## #s
#define WSTRINGIFY(s)	FREEZE_WSTR(s)
#define XAT_GIT_DESC	WSTRINGIFY(GIT_DESC)

// GenericHID pair
#define XAT_USB_VID	0x03EB
#define XAT_USB_PID	0x204F

#endif /* _VERSION_H_ */
