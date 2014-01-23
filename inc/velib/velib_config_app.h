#define VELIB_EXPECTED_TRACKING_NR	11

/* Use libevent, no threads and no special arguments */
#define CFG_WITH_TASK			1
#define CFG_WITH_TASK_LIBEVENT		1
#define CFG_WITH_LIBEVENT		1
#define CFG_NO_PREEMPTION		1
#define CFG_WITH_DEFAULT_ARGUMENTS 	1

/* Setup a CAN bus connection using a driver found at runtime */
#define CFG_INIT_CANBUS			1
#define CFG_WITH_CANHW_DRIVER		1
#include <velib/canhw/canhw_driver_config.h>

/* Enable dbus support */
#define CFG_WITH_VE_VALUES		1
#define CFG_WITH_VE_ITEM		1
#define CFG_WITH_VE_DBUS_ITEM		1
#define CFG_WITH_FLOAT			1
#define CFG_WITH_VARIANT		1
