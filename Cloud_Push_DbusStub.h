#pragma once

#include <cstdbool>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>

/* define valiables */

#define RAISE_ERROR(err)                \
	        do {                            \
			                dbus_error_free(&err);  \
			                return EXIT_FAILURE;    \
			        }while(0)

/* const declarations */
GMainLoop *mainloop = NULL ;
const char *version = "0.1";
const char *server_introspection_xml =
	DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE
	"<node>\n"

	"  <interface name='org.freedesktop.DBus.Introspectable'>\n"
	"    <method name='Introspect'>\n"
	"      <arg name='data' type='s' direction='out' />\n"
	"    </method>\n"
	"  </interface>\n"

	"  <interface name='org.freedesktop.DBus.Properties'>\n"
	"    <method name='Get'>\n"
	"      <arg name='interface' type='s' direction='in' />\n"
	"      <arg name='property'  type='s' direction='in' />\n"
	"      <arg name='value'     type='s' direction='out' />\n"
	"    </method>\n"
	"    <method name='GetAll'>\n"
	"      <arg name='interface'  type='s'     direction='in'/>\n"
	"      <arg name='properties' type='a{sv}' direction='out'/>\n"
	"    </method>\n"
	"  </interface>\n"

	"  <interface name='org.cloudPush.ServerInterface'>\n"
	"    <property name='Version' type='s' access='read' />\n"
	"    <method name='Ping' >\n"
	"      <arg type='s' direction='out' />\n"
	"    </method>\n"
	"    <method name='Echo'>\n"
	"      <arg name='string' direction='in' type='s'/>\n"
	"      <arg type='s' direction='out' />\n"
	"    </method>\n"
	"    <method name='EmitSignal'>\n"
	"    </method>\n"
	"    <method name='Quit'>\n"
	"    </method>\n"
	"    <signal name='OnEmitSignal'>\n"
	"    </signal>"
	"  </interface>\n"

"</node>\n";

/* class functions */

class Cloud_Push_DbusStub
{
	public:
	       Cloud_Push_DbusStub(){};
	       static DBusHandlerResult server_get_properties_handler(const char *property, DBusConnection *conn, DBusMessage *reply);
	       static DBusHandlerResult server_get_all_properties_handler(DBusConnection *conn, DBusMessage *reply);
	       int Cloud_Push_DbusStubInit();
	       static DBusHandlerResult server_message_handler(DBusConnection *conn, DBusMessage *message, void *data);
};
