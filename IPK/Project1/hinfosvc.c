#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

unsigned sleep(unsigned sec);

struct cpustats {
    unsigned long t_user;
    unsigned long t_nice;
    unsigned long t_system;
    unsigned long t_idle;
    unsigned long t_iowait;
    unsigned long t_irq;
    unsigned long t_softirq;
};

void get_stats(struct cpustats *st);
int calculate_load(struct cpustats *prev, struct cpustats *cur);
int get_cpu_usage();

char get_cpu_name(char cpu_name[256]);

char webpage[] =
    "HTTP/1.1 200 OK\r\nContent-Type: text/html: charset=UTF-8\r\n\r\n";

///////////////////////////////////////////////     MAIN        /////////////////////////////////////////////////
int main(int argc, char *argv[]){
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    int fd_server, fd_client;
    char buf[2048];
    int fdimg;
    int on = 1;
    int port;
    if(argc == 2){
        port = atoi(argv[1]);
    }
    else {
        fprintf(stderr, "Error : Incorrect number of arguments\n");
        exit(1);
    }
    
    fd_server = socket(AF_INET, SOCK_STREAM, 0); 
    if(fd_server < 0){
        fprintf(stderr, "Error : Failed to create socket\n");
        exit(1);
    }

    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if(bind(fd_server ,(struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        fprintf(stderr, "Error : Failed to process address\n");
        close(fd_server);
        exit(1);
    }

    if(listen(fd_server, 10) == -1){
        fprintf(stderr, "Error : Failed to accept connection\n");
        close(fd_server);
        exit(1);
    }

    while(1){
        fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);


        if(fd_client == -1){
            fprintf(stderr, "Error : Connection failed\n");
            continue;
        }

        printf("Client conencted...\n");

        if(!fork()){
            
            close(fd_server);
            memset(buf, 0, 2048);
            int reads = read(fd_client, buf, 2047);
            if(reads < 1){
                fprintf(stderr, "Error : Failed to read requests\n");
                continue;
            }

            if(strncmp(buf, "GET / ", 6) == 0){
                send(fd_client, webpage, strlen(webpage), 0);
            }
            if(strncmp(buf, "GET /cpu-name ", 14) == 0){

                char cpu_name[256];
                strcpy(cpu_name, webpage);
                char tmp[256];
                get_cpu_name(tmp);
                strcat(cpu_name, tmp);
                send(fd_client, cpu_name, strlen(cpu_name), 0);

            }
            
            if(strncmp(buf, "GET /load ", 10) == 0){
                char cpu_usage[256];
                strcpy(cpu_usage, webpage);
                int tmp;
                get_cpu_usage(tmp);
                char cpu[256];
                sprintf(cpu, "%d", tmp);
                strcat(cpu_usage, cpu);
                strcat(cpu_usage, "%\n");
                send(fd_client, cpu_usage, strlen(cpu_usage), 0);
            }

            if(strncmp(buf, "GET /hostname ", 14)==0){
                char tmp[256];
                char hostname[256];
                strcpy(hostname, webpage);
                gethostname(tmp, 256);
                strcat(hostname, tmp);
                strcat(hostname,"\n");
                send(fd_client, hostname, strlen(hostname), 0);
            }
            close(fd_client);
            
            exit(0);
        }
        close(fd_client);
        printf("closing..\n");
    }
    

   
    return 0;
}






void get_stats(struct cpustats *st){
    FILE *fp = fopen("/proc/stat", "r");
    char cpun[255];
    fscanf(fp, "%s %ld %ld %ld %ld %ld %ld %ld", cpun, &(st->t_user), &(st->t_nice), 
        &(st->t_system), &(st->t_idle), &(st->t_iowait), &(st->t_irq),
        &(st->t_softirq));
    fclose(fp);
	return;
}


int calculate_load(struct cpustats *prev, struct cpustats *cur){
    int idle_prev = (prev->t_idle) + (prev->t_iowait);
    int idle_cur = (cur->t_idle) + (cur->t_iowait);

    int nidle_prev = (prev->t_user) + (prev->t_nice) + (prev->t_system) + (prev->t_irq) + (prev->t_softirq);
    int nidle_cur = (cur->t_user) + (cur->t_nice) + (cur->t_system) + (cur->t_irq) + (cur->t_softirq);

    int total_prev = idle_prev + nidle_prev;
    int total_cur = idle_cur + nidle_cur;

    double totald = (double) total_cur - (double) total_prev;
    double idled = (double) idle_cur - (double) idle_prev;

    double cpu_perc = (1000 * (totald - idled) / totald + 1) / 10;

    return cpu_perc;
}

int get_cpu_usage(){
    struct cpustats stat0, stat1;
    get_stats(&stat0);
    sleep(1);
    get_stats(&stat1);
    
    return calculate_load(&stat0, &stat1);
}


char get_cpu_name(char cpu_name[256]){ 
    FILE* file = fopen("/proc/cpuinfo", "r"); 
    char line[256];
    
    int i = 0; 
    while (fgets(line, sizeof(line), file)) { 
        i++; 
        if(i == 5 ) 
        { 
            strcpy(cpu_name, &line[13]); 
            break;  
        } 
    } 
    fclose(file); 
    return *cpu_name; 
}
