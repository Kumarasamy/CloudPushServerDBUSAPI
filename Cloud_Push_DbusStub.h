#pragma once

#include <cstdbool>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>

/* define valiables */
#define DBUS_BUSNAME             "org.cloudpush.Server"
#define DBUS_INTERFACE_NAME_PATH "/org/cloudpush/ServerObj"
#define DBUS_OBJECTPATH         "/org/cloudpush/ServerObj"

#define RAISE_ERROR(err)                \
	        do {                            \
			                dbus_error_free(&err);  \
			                return EXIT_FAILURE;    \
			        }while(0)

/* const declarations */
const char *version = "0.1";
static const char *server_introspection_xml  =
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

"  <interface name='org.cloudpush.ServerInterface'>\n"
"    <property name='Version' type='s' access='read' />\n"
"    <method name='Hello' >\n"
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
"    </signal>"
"  </interface>\n"

"</node>\n";

/* class functions */

class CloudPushDbusStub
{
	private:
	       DBusConnection *conn;
	public:
	       CloudPushDbusStub();
	       static DBusHandlerResult Cloud_push_server_get_properties_handler(const char *property, DBusConnection *conn, DBusMessage *reply);
	       static DBusHandlerResult Cloud_push_server_Introspect( DBusMessage *message ,DBusConnection *conn ,DBusError err );
	       static DBusHandlerResult Cloud_push_server_get_all_properties_handler(DBusConnection *conn, DBusMessage *reply);
	       static DBusHandlerResult Cloud_push_server_Get( DBusMessage *message ,DBusConnection *conn , DBusError err );
	       static DBusHandlerResult Cloud_push_server_hello(DBusMessage *message ,DBusConnection *conn ,DBusError err );
	       static DBusHandlerResult Cloud_push_server_Signalhello(DBusMessage *message ,DBusConnection *conn ,DBusError err );
	       int Cloud_push_DbusInit(const char *busname,const char *objectpath );
	       static DBusHandlerResult Cloud1_push_server_message_handler(DBusConnection *conn, DBusMessage *message, void *data);
	       static DBusHandlerResult Cloud_push_server_message_handler(DBusConnection *conn, DBusMessage *message, void *data);
};
