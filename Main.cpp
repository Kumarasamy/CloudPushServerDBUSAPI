#include<iostream>
#include<errno.h>
#include "CloudPushOSWrapper.h"
#include "Cloud_Push_Server.h"

using namespace std;
using namespace CLOUD_PUSH ;

//main function
int main( int argc , char *argv[] )
{

  int retval = EINVAL ;
//CloudPushServerMain call
  CloudPushOSWrapper objCloudPushOSWrapper ;
  CloudPushServer objCloudPushServer;
  retval = objCloudPushServer.CloudPushServerMain(argc,argv);
  cout<<"EXIT_SUCCESS" <<retval<<endl;
  if( retval == EXIT_SUCCESS )
  {


	objCloudPushOSWrapper.CloudPushOSWrapperSemInit();
	objCloudPushOSWrapper.CloudPushOSWrapperSemLock();
         	
	//Wait for thread
	//TOO 
	//Signal handler init
	//Deinit the handler
  }

	return EXIT_SUCCESS;
}
