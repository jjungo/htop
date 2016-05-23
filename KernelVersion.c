/*
htop - KernelVersion.c
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "KernelVersion.h"
#include "CRT.h"
#include "KernelVersion.h"

#include <sys/utsname.h>
#include <string.h>

/*{
#include "Meter.h"
}*/


int KernelVersionMeter_attributes[] = {
   KERNELVERSION
};

static void KernelVersionMeter_updateValues(Meter* this, char* buffer, int len) {
    (void) this;
    if ((buffer != NULL) && (len > 0)) {
        struct utsname* datas = xMalloc(sizeof(struct utsname));
        if (uname(datas) == -1) {
            buffer = NULL;
            free(datas);
            return;
        }
        snprintf(buffer, len, "%s %s", datas->sysname, datas->release);
        free(datas);
    }
}

MeterClass KernelVersionMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete,
   },
   .updateValues = KernelVersionMeter_updateValues,
   .defaultMode = TEXT_METERMODE,
   .total = 1.0,
   .attributes = KernelVersionMeter_attributes,
   .name = "Kernel",
   .uiName = "Kernel version",
   .caption = "Kernel version: "
};
