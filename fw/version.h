#ifndef _VERSION_H_
#define _VERSION_H_

#define XAT_MAJOR	0
#define XAT_MINOR	3
#define XAT_PATCH	0

//#define GIT_DESC	"$(shell git describe)"

#ifndef GIT_DESC
#error GIT version description not defined!
#endif

#define FREEZE_WSTR_L(s)	L ## s
#define FREEZE_WSTR(s)		FREEZE_WSTR_L(#s)
#define WSTRINGIFY(s)		FREEZE_WSTR(s)

#define XAT_GIT_DESC		WSTRINGIFY(GIT_DESC)

// Thanks to OpenMoko Inc.
#define XAT_USB_VID	0x1d50
#define XAT_USB_PID	0x60c3

#define DEVICE_CAPS	"XAT-ROT-ALPHA;STEPPER=2;ENDSTOP=2;VBAT=1/3;VER=" STRINGIFY(GIT_DESC)

#endif /* _VERSION_H_ */
