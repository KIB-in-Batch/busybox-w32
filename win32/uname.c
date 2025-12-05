#include "libbb.h"
/* After libbb.h, since it needs sys/types.h on some systems */
#include <sys/utsname.h>

int uname(struct utsname *name)
{
    const char *unk = "unknown";
    OSVERSIONINFO os_info;
    SYSTEM_INFO sys_info;

    strcpy(name->sysname, "Linux");

    if ( gethostname(name->nodename, sizeof(name->nodename)) != 0 ) {
        strcpy(name->nodename, unk);
    }

    memset(&os_info, 0, sizeof(OSVERSIONINFO));
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    sprintf(name->release, "5.4.300");
    sprintf(name->version, "#1 SMP PREEMPT_DYNAMIC Thu Jun  5 18:30:46 UTC 2025 "); 
    
    GetSystemInfo(&sys_info);
    switch (sys_info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
		strcpy(name->machine, "x86_64");
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		strcpy(name->machine, "i686");
		if (sys_info.wProcessorLevel < 6) {
			name->machine[1] = '3';
		}
		break;
#if defined(PROCESSOR_ARCHITECTURE_ARM64)
	case PROCESSOR_ARCHITECTURE_ARM64:
		strcpy(name->machine, "aarch64");
		break;
#endif
	default:
		strcpy(name->machine, unk);
		break;
	}

	return 0;
}
