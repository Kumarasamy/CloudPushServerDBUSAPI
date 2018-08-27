#pragma once
#include<cstring>
#include<curl/curl.h>
#include<cstdlib>
#include<iostream>
#include<string>

#define EMPTY ""
using namespace std;
class Cloud_Push_Curl
{
    private:
    
    typedef struct s_curl
    {     
      CURL *curl;
      CURLcode res;	
      struct curl_slist *headers;
      string cloudURL;
    }s_curl;
    
    typedef struct userdetails
    {
	string username;
	string password;
    }userdetails;
    s_curl st_curl ;

    public:

    Cloud_Push_Curl() 
    {
    }

    void setCurlURL(string url)
    {
	st_curl.cloudURL = url;
    }

    void Curl_Init(string url)
    {
	curl_global_init(CURL_GLOBAL_ALL);	
	st_curl.curl = curl_easy_init();
	st_curl.cloudURL =  url;
	st_curl.headers =  NULL;
	if(st_curl.curl && st_curl.cloudURL != EMPTY) 
	{
	    curl_easy_setopt(st_curl.curl, CURLOPT_URL,st_curl.cloudURL.c_str());
	}
    }

    void SetHeader()
    {
      st_curl.headers = curl_slist_append(st_curl.headers, "Expect:");
      st_curl.headers = curl_slist_append(st_curl.headers, "Content-Type: application/json");
      curl_easy_setopt(st_curl.curl, CURLOPT_CUSTOMREQUEST, "POST");
      curl_easy_setopt(st_curl.curl, CURLOPT_HTTPHEADER, st_curl.headers);
      curl_easy_setopt(st_curl.curl, CURLOPT_POSTFIELDSIZE, -1L);
    } 

    void SetUserUserName(string username,string password)
    {
	curl_easy_setopt(st_curl.curl, CURLOPT_USERNAME,username.c_str());
	curl_easy_setopt(st_curl.curl, CURLOPT_PASSWORD,password.c_str());
    }
    
    void SetCurlData(string jsonvalue )
    {
	  curl_easy_setopt(st_curl.curl, CURLOPT_POSTFIELDS, jsonvalue);
	  st_curl.res = curl_easy_perform(st_curl.curl);
	  if(st_curl.res != CURLE_OK)
	  {
	     std::cout<<"curl_easy_perform() failed: \n",
	     std::cout<<curl_easy_strerror(st_curl.res);
     
		/* always cleanup */ 
	     curl_easy_cleanup(st_curl.curl);
	     curl_slist_free_all(st_curl.headers);
	  }
	curl_global_cleanup();
    }    
};

int main()
{
    Cloud_Push_Curl obj;            
    obj.Curl_Init("http://localhost:5555");
    obj.SetHeader();
    string jsonvalue = "{ username : kumarasamy}";
    obj.SetCurlData(jsonvalue);
}
