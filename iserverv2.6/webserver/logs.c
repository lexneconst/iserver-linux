
#include "iserver.h"

char *get_realtime(void){
    //char ptr[MAX_PATH];
	char *p = NULL;
	time_t     t;
	struct tm *m;
	
    do{
    p = (char *) malloc( 64 );
    if(p==NULL){
        fatal("allocate memory ", __FILE__, __FUNCTION__, __LINE__);
        break;
    }
	t = time(NULL);
	m = localtime(&t);
	
	sprintf(p, "%02d-%02d-%02d %02d-%02d-%02d-%04d", 
		   m->tm_hour, m->tm_min, m->tm_sec, 
		   m->tm_wday, m->tm_mday , m->tm_mon+1 , m->tm_year+1900 );
		   
	if(p[strlen(p)-1] == '\n')
	   p[strlen(p)-1] = '\0';
	}while(0);

	return p;
}



uint32_t clogs(iserver_config *s){
	printf("%s : %x \n", __FUNCTION__, s);
}

uint32_t caccess(iserver_config *s)
{
	printf("%s : %x \n", __FUNCTION__, s);
}


uint32_t ulogs_access(zlogs_data *s)
{
	printf("%s %s %s %s\n", s->ipaddr,  s->fulldate, s->request, s->logs );
	return 0;
}
