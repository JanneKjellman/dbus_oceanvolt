#include <stdio.h>
#include <stdint.h>

#include <velib/canhw/canhw.h>
#include <velib/platform/console.h>
#include <velib/types/ve_dbus_item.h>
#include <velib/types/ve_item.h>
#include <velib/types/ve_values.h>

typedef struct {
	VeItem valueA;
	VeItem valueB;
} Device;

static Device dev;

int32_t motorRPM;
float motorVoltage;
float motorCurrent;

/* Connect to the dbus and publish some values */
void addDevice(void)
{
	VeItem *root = veValueTree();
	struct VeDbus *conn;
	VeVariant v;

	/* Reset Motor values */
	motorRPM = 0;
	motorVoltage = 0;
	motorCurrent = 0;

	/* Add values which should be accessible on the dbus */
	veItemAddChildByUid(root, "Test/ValueA", &dev.valueA);
	veItemAddChildByUid(root, "Test/ValueB", &dev.valueB);

	/* The ccgx uses the system dbus, a good candidate for an argument */
#if defined(TARGET_pc)
	conn = veDbusConnect(DBUS_BUS_SESSION);
#else
	conn = veDbusConnect(DBUS_BUS_SYSTEM);
#endif

	if (conn == NULL) {
		printf("dbus_service: no dbus connection\n");
		pltExit(10);
	}

	/* make the values available on the dbus and get a service name */
	veDbusItemInit(conn, root);
	if (!veDbusChangeName(conn, "com.victronenergy.motordrive")) {
		printf("dbus_service: registering name failed\n");
		pltExit(11);
	}

	/*
	 * Set some example data. This uses the "owner" version. The regular
	 * set will invoke an (optional) callback intended to send new values
	 * from the dbus towards the CAN bus and will not update the value
	 * directly. When the new value is confirmed on the CAN-bus, the
	 * veItemOwnerSet will update the value and send a valueChanged back
	 * to the dbus confirming that the change was made. If the veItemSet
	 * was used it would invoke the callback to send it to the CAN-bus
	 * again in an attempt to set the value it just received.
	 */
	veItemOwnerSet(&dev.valueA, veVariantUn32(&v, 2));
	veItemOwnerSet(&dev.valueB, veVariantStr(&v, "Example String"));
}

/* Called after CAN is already setup */
void taskInit(void)
{
  /* normally this is done after a device is found on the CAN bus */
  addDevice();
}

void taskUpdate(void)
{
	VeRawCanMsg msg;

	while (veCanRead(&msg))
	{
		un8 n;

		/* ignore all 29 bit / extended messages */
		/* if (msg.flags & VE_CAN_EXT) */
		/*	continue; */

		switch (msg.canId)
		  {
		  case 0x132: /* Sevcon RPM message convert to signed int32 */
		    { motorRPM = (msg.mdata[3] << 24) | (msg.mdata[2] << 16) | (msg.mdata[1] << 8) | msg.mdata[0]; }
		    break;
		  case 0x162: /* Bat voltage, Contrl Temp, Bat current, Torq */
		    {
		      motorVoltage = (float)((signed short)(msg.mdata[1] << 8) | msg.mdata[0]) * 0.0625;
		      motorCurrent = (float)((signed short)(msg.mdata[4] << 8) | msg.mdata[3]) * 0.0625;
		    }
		    break;
		  }

		/* printf("msg id:%X dlc:%d flags: %d", msg.canId, msg.length, msg.flags);
		for (n = 0; n < msg.length; n++)
			printf(" %02X", msg.mdata[n]);
			putchar('\n'); */

		printf("Motor rpm: %d voltage: %.1f current: %.1f\n", motorRPM, motorVoltage, motorCurrent);
		/* note: io has a bunch of helpers to parse a byte array */}
		
}

/* 50ms time progress */
void taskTick(void)
{
}
