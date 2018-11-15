
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int parse_command( char *command, char **cmds )
{
	int i;
	char *p;
	p = strtok( command , "|" ); 
	for(i=0; p; i++)
	{
		cmds[i] = p;
		p = strtok( 0 , "|" ); 
	}
	return i;
}

int main()
{
	char command[1024];
	char *cmds[128];

	int ncmd=0;
	int i;
	int fds[128][2];

	while(1)
	{
		printf("myshell>");
		fflush(stdout);
		if (fgets( command, sizeof command, stdin ) == NULL) 
		{
			break;
		}

		command[ strlen(command)-1 ] = 0;

		if( strcmp( command , "exit" ) == 0 )
			break;

		ncmd = parse_command( command, cmds );

		for(i=0; i<ncmd; i++ )
		{
			if( i < ncmd-1 )
				pipe( fds[i] );

			if( fork() == 0 )
			{
				if(i!=0)
					dup2( fds[i-1][0], 0 );

				if( i!=(ncmd-1) )
					dup2( fds[i][1], 1 );

				execl("/bin/sh", "sh", "-c", cmds[i], (char *) 0);
			}
			if(i!=0)
				close( fds[i-1][0] );
			if(i!=(ncmd-1))
				close( fds[i][1] );
		}
		while( wait(0) > 0 )
			;
	}
	return 0;
}

