#include "Cloud_Push_DbusStub.h"

/* class functions definitions*/
CloudPushDbusStub::CloudPushDbusStub()
{

}

DBusHandlerResult CloudPushDbusStub::Cloud_push_server_get_properties_handler(const char *property, DBusConnection *conn, DBusMessage *reply)
{
	if (!strcmp(property, "Version")) {
		dbus_message_append_args(reply,
				DBUS_TYPE_STRING, &version,
				DBUS_TYPE_INVALID);
	} else
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (!dbus_connection_send(conn, reply, NULL))
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	return DBUS_HANDLER_RESULT_HANDLED;
}

DBusHandlerResult CloudPushDbusStub::Cloud_push_server_get_all_properties_handler(DBusConnection *conn, DBusMessage *reply)
{
	DBusHandlerResult result;
	DBusMessageIter array, dict, iter, variant;
	const char *property = "Version";

	/*
	 * All dbus functions used below might fail due to out of
	 * memory error. If one of them fails, we assume that all
	 * following functions will fail too, including
	 * dbus_connection_send().
	 */
	result = DBUS_HANDLER_RESULT_NEED_MEMORY;

	dbus_message_iter_init_append(reply, &iter);
	dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "{sv}", &array);

	/* Append all properties name/value pairs */
	property = "Version";
	dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, NULL, &dict);
	dbus_message_iter_append_basic(&dict, DBUS_TYPE_STRING, &property);
	dbus_message_iter_open_container(&dict, DBUS_TYPE_VARIANT, "s", &variant);
	dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &version);
	dbus_message_iter_close_container(&dict, &variant);
	dbus_message_iter_close_container(&array, &dict);

	dbus_message_iter_close_container(&iter, &array);

	if (dbus_connection_send(conn, reply, NULL))
		result = DBUS_HANDLER_RESULT_HANDLED;
	return result;
}

/* static DBusHandlerResult CloudPushDbusStub::cloud_push_server_error_message_handler(DBusConnection *conn, DBusMessage *message,DBusMessage *reply,
		DBusHandlerResult result ,DBusError err )
{
	if (dbus_error_is_set(&err)) {
		if (reply)
			dbus_message_unref(reply);
		reply = dbus_message_new_error(message, err.name, err.message);
		dbus_error_free(&err);
	}

	if (!reply)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	result = DBUS_HANDLER_RESULT_HANDLED;
	if (!dbus_connection_send(conn, reply, NULL))
		result = DBUS_HANDLER_RESULT_NEED_MEMORY;
	dbus_message_unref(reply);

	return result;
} */

/*static DBusHandlerResult CloudPushDbusStub::Cloud_push_server_Introspect( DBusMessage *message ,DBusConnection *conn ,DBusError err )
{
	printf("hello i am inside\n");
	DBusMessage *reply = NULL;
	DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;;

	reply = dbus_message_new_method_return(message);
	if( reply == NULL )
	{
		result = cloud_push_server_error_message_handler(conn,message,reply,result,err);
	}

	dbus_message_append_args(reply,
			DBUS_TYPE_STRING, &server_introspection_xml,
			DBUS_TYPE_INVALID);
	printf("Done job");
	return result;

}*/

/*static DBusHandlerResult CloudPushDbusStub::Cloud_push_server_Get( DBusMessage *message ,DBusConnection *conn , DBusError err )
{
	DBusMessage *reply = NULL;
	DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;
	const char *interface, *property;

	if (!dbus_message_get_args(message, &err,
				DBUS_TYPE_STRING, &interface,
				DBUS_TYPE_STRING, &property,
				DBUS_TYPE_INVALID))
	{
		return (cloud_push_server_error_message_handler(conn,message,reply,result,err));

	}

	if (!(reply = dbus_message_new_method_return(message)))
	{
		return (cloud_push_server_error_message_handler(conn,message,reply,result,err));

	}

	result = Cloud_push_server_get_properties_handler(property, conn, reply);
	dbus_message_unref(reply);
	return result;

}*/

/*static DBusHandlerResult CloudPushDbusStub::Cloud_push_server_GetAll( DBusMessage *message ,DBusConnection *conn ,DBusError err )
{
	DBusMessage *reply = NULL;
	DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;

	reply = dbus_message_new_method_return(message);
	if( reply == NULL )
	{
		return (cloud_push_server_error_message_handler(conn,message,reply,result,err));
	}
	result = Cloud_push_server_get_all_properties_handler(conn, reply);
	dbus_message_unref(reply);
	return result;

}*/

/*static DBusHandlerResult CloudPushDbusStub::Cloud_push_server_hello( DBusMessage *message ,DBusConnection *conn ,DBusError err )
{
	DBusMessage *reply = NULL;
	DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;
	const char *mess = "Hello World";

	reply = dbus_message_new_method_return(message);

	if( reply == NULL )
	{
		return (cloud_push_server_error_message_handler(conn,message,reply,result,err));
	}

	dbus_message_append_args(reply,
			DBUS_TYPE_STRING, &mess,
			DBUS_TYPE_INVALID);
}

static DBusHandlerResult CloudPushDbusStub::Cloud_push_server_Signalhello( DBusMessage *message ,DBusConnection *conn ,DBusError err )
{
	DBusMessage *reply = NULL;
	DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;

	reply = dbus_message_new_signal( DBUS_OBJECTPATH,
			DBUS_BUSNAME,
			"OnHelloSignal");

	if( reply == NULL )
	{
		return (cloud_push_server_error_message_handler(conn,message,reply,result,err));
	}
	if (!dbus_connection_send(conn, reply, NULL))
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	reply = dbus_message_new_method_return(message);


}*/


int CloudPushDbusStub::Cloud_push_DbusInit(const char *busname,const char *objectpath )
{

	GMainLoop *mainloop = NULL;

	DBusError err;
	int rv;
	dbus_error_init(&err);

	static const DBusObjectPathVTable Cloud_pushserver_vtable = {
		.message_function = &CloudPushDbusStub::Cloud_push_server_message_handler
	};

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

	if (conn == NULL )
	{
		fprintf(stderr, "Failed to get a session DBus connection: %s\n", err.message);
		RAISE_ERROR(err);
	}

	rv = dbus_bus_request_name(conn, DBUS_BUSNAME, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);

	if (rv != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
	{
		fprintf(stderr, "Failed to request name on bus: %s\n", err.message);

	}

	if (!dbus_connection_register_object_path(conn,DBUS_OBJECTPATH, &Cloud_pushserver_vtable, NULL))
	{
		fprintf(stderr, "Failed to register a object path for 'TestObject'\n");
	}

	printf("Starting dbus tiny server v%s\n", version);
	mainloop = g_main_loop_new(NULL, false);
	dbus_connection_setup_with_g_main(conn, NULL);
	g_main_loop_run(mainloop);

	return EXIT_SUCCESS;
}

/*static DBusHandlerResult CloudPushDbusStub::Cloud1_push_server_message_handler(DBusConnection *conn, DBusMessage *message, void *data)
{

	DBusHandlerResult result;
	DBusMessage *reply = NULL;
	DBusError err;

	fprintf(stderr, "Got D-Bus request: %s.%s on %s\n",
			dbus_message_get_interface(message),
			dbus_message_get_member(message),
			dbus_message_get_path(message));

	dbus_error_init(&err);

	if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE, "Introspect")) {
		result = Cloud_push_server_Introspect(message,conn,err);
		return result;
	}

	else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "Get"))
	{

		result =  Cloud_push_server_Get (message,conn,err);
		return result ;
	}

	else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "GetAll"))
	{

		result = Cloud_push_server_GetAll(message,conn,err);
		return result;
	}

	else if (dbus_message_is_method_call(message, DBUS_BUSNAME, "Hello"))
	{
		result = Cloud_push_server_Signalhello(message,conn,err);
		return result;

	}

	else if (dbus_message_is_method_call(message, DBUS_BUSNAME, "Echo"))
	{

	}
	else if (dbus_message_is_method_call(message,DBUS_BUSNAME , "EmitSignal"))
	{

	}

	else if (dbus_message_is_method_call(message, DBUS_BUSNAME,"Quit"))
	{
		reply = dbus_message_new_method_return(message);

	}
	else
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	return result;
}*/

DBusHandlerResult CloudPushDbusStub::Cloud_push_server_message_handler(DBusConnection *conn, DBusMessage *message, void *data)
{
	GMainLoop *mainloop = NULL ;
	DBusHandlerResult result;
  DBusMessage *reply = NULL;
	DBusError err;
	bool quit = false;

	fprintf(stderr, "Got D-Bus request: %s.%s on %s\n",
		dbus_message_get_interface(message),
		dbus_message_get_member(message),
		dbus_message_get_path(message));

	/*
	 * Does not allocate any memory; the error only needs to be
	 * freed if it is set at some point.
	 */
	dbus_error_init(&err);

	if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE, "Introspect")) {

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		dbus_message_append_args(reply,
					 DBUS_TYPE_STRING, &server_introspection_xml,
					 DBUS_TYPE_INVALID);

	}  else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "Get")) {
		const char *interface, *property;

		if (!dbus_message_get_args(message, &err,
					   DBUS_TYPE_STRING, &interface,
					   DBUS_TYPE_STRING, &property,
					   DBUS_TYPE_INVALID))
			goto fail;

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		result = Cloud_push_server_get_properties_handler(property, conn, reply);
		dbus_message_unref(reply);
		return result;

	}  else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "GetAll")) {

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		result = Cloud_push_server_get_all_properties_handler(conn, reply);
		dbus_message_unref(reply);
		return result;

	}  else if (dbus_message_is_method_call(message, "org.example.TestInterface", "Ping")) {
		const char *pong = "Pong";

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		dbus_message_append_args(reply,
					 DBUS_TYPE_STRING, &pong,
					 DBUS_TYPE_INVALID);

	} else if (dbus_message_is_method_call(message, "org.example.TestInterface", "Echo")) {
		const char *msg;

		if (!dbus_message_get_args(message, &err,
					   DBUS_TYPE_STRING, &msg,
					   DBUS_TYPE_INVALID))
			goto fail;

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		dbus_message_append_args(reply,
					 DBUS_TYPE_STRING, &msg,
					 DBUS_TYPE_INVALID);

	} else if (dbus_message_is_method_call(message, "org.example.TestInterface", "EmitSignal")) {

		if (!(reply = dbus_message_new_signal("/org/example/TestObject",
						      "org.example.TestInterface",
						      "OnEmitSignal")))
			goto fail;

		if (!dbus_connection_send(conn, reply, NULL))
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		/* Send a METHOD_RETURN reply. */
		reply = dbus_message_new_method_return(message);

	} else if (dbus_message_is_method_call(message, "org.example.TestInterface", "Quit")) {
		/*
		 * Quit() has no return values but a METHOD_RETURN
		 * reply is required, so the caller will know the
		 * method was successfully processed.
		 */
		reply = dbus_message_new_method_return(message);
		quit  = true;

	} else
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

fail:
	if (dbus_error_is_set(&err)) {
		if (reply)
			dbus_message_unref(reply);
		reply = dbus_message_new_error(message, err.name, err.message);
		dbus_error_free(&err);
	}

	/*
	 * In any cases we should have allocated a reply otherwise it
	 * means that we failed to allocate one.
	 */
	if (!reply)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Send the reply which might be an error one too. */
	result = DBUS_HANDLER_RESULT_HANDLED;
	if (!dbus_connection_send(conn, reply, NULL))
		result = DBUS_HANDLER_RESULT_NEED_MEMORY;
	dbus_message_unref(reply);

	if (quit) {
		fprintf(stderr, "Server exiting...\n");
		g_main_loop_quit(mainloop);
	}
	return result;
}

int main()
{
	CloudPushDbusStub obj;
	obj.Cloud_push_DbusInit(DBUS_BUSNAME,DBUS_OBJECTPATH);
}
