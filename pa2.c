
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
typedef struct node{
  pid_t pid;
  char *name;
  struct node *left,*right;
}node;

static char *home;

static node *head = NULL;

void Eliminate(char *str, char ch);
const char *get_filetype(struct stat *buf);
int has_apos(char * str);
node *create(pid_t pid,char *proc_name);
int isEmpty(node *head);
void insert(pid_t pid,char *proc_name);
void delete(node *p);
void signalHandler(int sig_num);
void getjobnumber(int jobnum);
void sendsignal(int jobnum,int signum);
void listjobs(int flag);
void runproc(char *command[],int bckgrnd);
void curworkdir(char buf[]);
void sethomdir();
char *gethomdir();
char *removespace(char *input);
char *redirect(char *input);
void parseinput(char *input);
void process(char *command[],char *argument);
void parseinput(char *input);
int child_dir(char *actpath,char *curpath);
int substr(char *actpath,char *curpath);
void getuserdetails(char username[],char pc_name[]);


int main()
{
  char  *ctrld,*cwd, input[100000], username[100],  pc_name[100];
  cwd = (char *)malloc(sizeof(char)*100);
  int IN,OUT;
  getuserdetails(username,pc_name);
  sethomdir();
  IN = dup(STDIN_FILENO);
  OUT = dup(STDOUT_FILENO);
  for(;;){
    dup2(STDIN_FILENO,IN);
    dup2(STDOUT_FILENO,OUT);
    curworkdir(cwd);
    listjobs(1);
    if(!strcmp(gethomdir(),cwd));
    // printf("%s@%s:~$ ",username,pc_name);
    else if(substr(gethomdir(),cwd))
      {
      cwd += child_dir(gethomdir(),cwd);
     // printf("%s@%s:~%s$ ",username,pc_name,cwd);
      }
    else;
     // printf("%s@%s:~%s$ ",username,pc_name,cwd);
    signal(SIGINT,signalHandler);
    signal(SIGTSTP,signalHandler);
    ctrld = fgets(input,1000,stdin);
    
    
      input[strlen(input)-1] = '\0';
   
    parseinput(input);
  }
  free(cwd);
  return 0;
}


int isEmpty(node *head)
{
  if(head == NULL)
    return 1;
  else
    return 0;
}

node *create(pid_t pid,char *proc_name)
{
  node *p = (node *)malloc(sizeof(node));
  p->name = (char *)malloc(sizeof(char)*100);
  p->pid = pid;
  strcpy(p->name,proc_name);
  p->left = NULL;
  p->right = NULL;
  return p;
}

void insert(pid_t pid,char *proc_name)
{
  node *tmp,*p;
  p = create(pid,proc_name);
  if(head == NULL)
    {  head = p;
      return; }
  tmp = head;
  while(tmp->right!=NULL)
    tmp = tmp->right;
  tmp->right = p;
  p->left = tmp;
  p->right = NULL;
  return;
}

void delete(node *p)
{
  if(p == head){
    free(p);
    head = head->right;
    return;
  }
  if(p->right == NULL){
    p->left->right = NULL;
    free(p);
    return;
   }
  p->left->right = p->right;
  p->right->left = p->left;
  free(p);
  return;
}

void signalHandler(int sig_num)
{
  if(sig_num == SIGINT){}
  return;
}

void getjobnumber(int jobnum)
{
  node *p;char *X[10] = {NULL};
  int stat,flag = 0,i = 1;
  p = head;
  while(p!=NULL){
    if(jobnum == i){
      flag = 1;
      break;
    }
    p=p->right;
    i++;
  }
  if(flag){
    while(wait(&stat)!=p->pid);
    delete(p);
  }
  return;
}

void sendsignal(pid_t pid,int sig_num){
  kill(pid,sig_num);
}

void listjobs(int flag)
{
    int status;
    node *p;
    p = head;
    while(p != NULL){
      if(flag == 1){
        if(waitpid(p->pid,&status,WNOHANG)){
         
          kill(p->pid,SIGKILL);
          delete(p);
          }
        p = p->right;
      }
      else if(flag == 2){
        if(waitpid(p->pid,&status,WNOHANG)){
         
          kill(p->pid,SIGKILL);
          delete(p);
          }
        
          
        p = p->right;
      }
      else{
        if(waitpid(p->pid,&status,WNOHANG)){
          
          kill(p->pid,SIGKILL);
          delete(p);
          }
        else
          kill(p->pid,SIGKILL);
        p = p->right;
      }
    }
  return;
}

void runproc(char *command[],int bckgrnd)
{
  int stat;
  pid_t pid;  int status;
  pid = fork();
  if(pid < 0){
    perror("process not created : ");
    exit(1);
    }
  if(pid == 0){
    if(bckgrnd){
      fclose(stdin);
      fopen("/dev/null", "r");
      if(execvp(command[0],command) == -1){
        fprintf(stderr,"mysh: Command not found\n");
        exit(1);
        }
      }
  else{
    if(execvp(command[0],command) == -1){
      fprintf(stderr,"mysh: Command not found\n");
      exit(1);
      }
    }
  }
  else{
    if(bckgrnd){
      insert(pid,command[0]);
      printf("[%d]  %s\n",pid,command[0]);
      }
    else{
      insert(pid,command[0]);
      waitpid(pid,&status,WUNTRACED);
      if(WIFSTOPPED(status))
        fprintf(stderr, "\n[%d]+ stop %s\n",pid,command[0] );
      else{     
        
          kill(pid,SIGKILL);
       }
      }
    }
  }

void curworkdir(char buf[]){ getcwd(buf,100); }

void sethomdir()
{
    home = (char *)malloc(sizeof(char)*100);
    getcwd(home,100);
}

char *gethomdir(){  return home;  }

void process(char *command[],char *argument)
{
  char txt[1000],cwd[100],newarg[100]={'\0'},*buf,*str,*token,*saveptr,*argv[3];
  int line,fd,flag = 0;
  struct stat statbuf;
  stat(argument,&statbuf);
  if(argument[strlen(argument)-1] == '&'){
    argument[strlen(argument)-1] = '\0';
    flag = 1;
    }
    if(!strcmp(command[0],"cd")){
      if(argument[0] == '~'){
        strcat(newarg,home);
        strcat(newarg,argument+1);
        argument = newarg;
      }
    if(access(argument,F_OK) == 0)
      {
        if(strcmp(get_filetype(&statbuf),"directory")==0)
          chdir(argument);
        else
        fprintf(stderr, "cd: Not a directory\n");
      }
    else{
      if (errno == ENOTDIR)
        fprintf(stderr, "cd: Not a directory\n");
      else if(errno == EACCES ||errno ==EPERM)
        fprintf(stderr, "cd: Permission denied\n");
      else if(errno==ENOENT)
         fprintf(stderr, "cd: No such file or directory\n");
      else 
         fprintf(stderr, "cd: %d\n", errno);
         
     // perror(argument);
      }
    }
  else if (!strcmp(command[0],"pinfo")){
    curworkdir(cwd);
    chdir("/proc");
    if(access(argument,F_OK) == 0){
      chdir(argument);
      buf = (char *)malloc(sizeof(char)*100000);
      fd = open("status",O_RDONLY);
      read(fd,buf,10000);
      for(line = 1, str = buf; ;line++, str = NULL){
        token = strtok_r(str,"\n",&saveptr);
        if(token == NULL)
            break;
        if(line == 1 || line == 2 || line == 5 || line == 17)
            puts(token);
        }
      }
      else
        perror(argument);
      chdir(cwd);
    }
    else if(!strcmp(command[0],"pwd")){
      curworkdir(cwd);
      puts(cwd);
    }
    else if (!strcmp(command[0],"echo")){
      if(argument[strlen(argument)-2] == '\"')
        argument[strlen(argument)-2] = '\0';
      if(argument[0] == '\"')
        argument += 1;
      printf("%s\n",argument);
    }
    else if(!strcmp(command[0],"listjobs"))
      listjobs(2);
    else if(!strcmp(command[0],"killallbg"))
      listjobs(3);
    else if(!strcmp(command[0],"fg"))
      getjobnumber(atoi(argument));
    else if(!strcmp(command[0],"exit"))
    {
      if(argument != NULL)
       {
          int n = atoi(argument);
          exit(n);      
      }
      else exit(0);
    }
    else if( access(argument,F_OK)!=0 &&(strcmp(command[0], "mv")==0||strcmp(command[0], "cp")==0))
    {
      if (errno == ENOTDIR)
        fprintf(stderr, "%s: Not a directory\n",command[0] );
      else if(errno == EACCES ||errno ==EPERM)
        fprintf(stderr, "%s: Permission denied\n",command[0]);
      else if(errno==ENOENT)
         fprintf(stderr, "%s: No such file or directory\n",command[0]);
      else 
         fprintf(stderr, "%s: %d\n", command[0], errno );
    }
    else if(strcmp(command[0], "awk")==0)
    {
      int a=0;
      int apos =0;
      // while(command[a]!= NULL)
      //         {
      //           printf("%d:  %s\n", a++, command[a]);
      //         }
      int count=0; 
      char nn[] = " ";
      while(command[count] != NULL)
      {
        if(has_apos(command[count]))
          apos++;
          count++;              
      }
      
      char*awk_command[200]={NULL};
      awk_command[0]=command[0];     
      int i=0;
      
      int j;
      if(apos<2)
      runproc(command,flag);
      else if (apos ==2){
       if(has_apos(command[1]))
          {          
             
            Eliminate(command[1], '\'');
            j=2;
             while(j < count &&!has_apos(command[j]) )
             {
               //printf("j:%d count : %d\n", j, count);     
               strcat(command[1], command[j]);  
               strcat(command[1], nn);   
                   
               j++;               
             }
             if( j <count&& has_apos(command[j]))
                {
                  apos++;
                  Eliminate(command[j], '\'');
                  strcat(command[1], command[j]);
                  strcat(command[1], nn);
                  awk_command[1]=command[1];   
                  j++;             
                }
                
          }
          
        
              i=2;
              while(command[j]!= NULL)
              {
                awk_command[i]=command[j];
                i++;
                j++;
              }
	     	if(access(awk_command[i-1],F_OK) != 0)
              {
                if(errno == EACCES ||errno ==EPERM)
                     fprintf(stderr, "awk: Permission denied\n");
                else if(errno==ENOENT)
                      fprintf(stderr, "awk: No such file or directory\n");
                 else 
                    fprintf(stderr, "awk: %d\n", errno);
		 exit(1);
              }
              int l =0;           
              runproc(awk_command,flag);
          }
      }
      else
       runproc(command,flag);
    
}

char *removespace(char *input)
{
  char *output;
  int i = 0,j = 0;
  output = (char *)malloc(sizeof(char)*100);
  for(i = 0; i < strlen(input); i++)
    if(input[i] != ' ')
      break;
  int start = i;
  for(i = strlen(input)-1; i>=0; i--)
    if(input[i] != ' ')
      break;
  int end = i;
  for(i = start;i <= end; i++)
    output[j++] = input[i];
  return output;
}

char *redirect(char *input)
{
  int stat,j,i;
	char symbol[2]={'\0'},*X[10] = { NULL };
	for(i = 0;i < strlen(input); i++){
		if(input[i] == '<')
			strcat(symbol,"<");
		if(input[i] == '>')
			strcat(symbol,">");
	}
	i = 0;
	char *str1,*str2,*token,*subtoken,*newarg[100]={NULL};
	char *saveptr1,*saveptr2,*arg[100]={NULL};
  for (j = 1, str1 = input; ; j++, str1 = NULL) {
  	token = strtok_r(str1,">", &saveptr1);
    if (token == NULL)
    	break;

    for (str2 = token; ; str2 = NULL) {
    	subtoken = strtok_r(str2,"<", &saveptr2);
      if (subtoken == NULL)
      	break;
			arg[i++] = subtoken;
		}
	}
  for(j = 0; j < i; j++)
    arg[j] = removespace(arg[j]);

    if(strcmp(symbol,"<") == 0){
      int fd1 = open(arg[1],O_RDONLY);
      if(fd1<0)
      {
        fprintf(stderr, "mysh: No such file\n");
        exit(1);
      }
      dup2(fd1, STDIN_FILENO);
      close(fd1);
      X[0] = arg[0];
      }
    else if(strcmp(symbol,"<>") == 0){
     
      int fd1 = open(arg[1],O_RDONLY);
      if(fd1<0)
      {
        fprintf(stderr, "mysh: No such file\n");
        exit(1);
      }
      dup2(fd1, STDIN_FILENO);
      close(fd1);
      int fd0 = creat(arg[2], 0644);
      dup2(fd0, STDOUT_FILENO);
      close(fd0);
      X[0] = arg[0];
    }
    else if(strcmp(symbol,"><") == 0){
      int fd1 = open(arg[2],O_RDONLY);
      dup2(fd1, STDIN_FILENO);
      close(fd1);
      int fd0 = creat(arg[1], 0644);
      dup2(fd0, STDOUT_FILENO);
      close(fd0);
      X[0] = arg[0];
    }
    else	{
      int j,i = 0;
      int fd0 = creat(arg[1], 0644);
      char *token,*saveptr1,*str1;
      dup2(fd0, STDOUT_FILENO);
      close(fd0);
        X[0] = arg[0];
        }
    return X[0];
}

void redirect_pipe(char input[])
{
  char *str1, *token;
  char *argv[100]={NULL},*saveptr1;
  int stat,i = 0,fd_in = 0,filedes[2],j;
  pid_t pid;
  for (j = 1, str1 = input; ; j++, str1 = NULL) {
    token = strtok_r(str1,"|", &saveptr1);
    if (token == NULL)
      break;
    argv[i++] = token;
  }
  i = 0;
  while (argv[i] != NULL)
  {
    int redir = 0;
    for(int k = 0; k < strlen(argv[i]); k++)
      if(argv[i][k] == '<'||argv[i][k] == '>')
        redir = 1;
      pipe(filedes);
      pid = fork();
      if(pid < 0)
        exit(EXIT_FAILURE);
      else if (pid == 0) {
        char *str1,*saveptr1,*token,*X[10] = {NULL};
        if(redir)
        argv[i] = redirect(argv[i]);
        dup2(fd_in,STDIN_FILENO);
        if (argv[i+1]!= NULL)
          dup2(filedes[1],STDOUT_FILENO);
        close(filedes[0]);
        int j,k = 0;
        for (j = 1, str1 = argv[i]; ; j++, str1 = NULL) {
        	token = strtok_r(str1," ", &saveptr1);
          if (token == NULL)
          	break;
      		X[k++] = token;
      	}
        execvp(X[0],X);
        exit(EXIT_FAILURE);
      }
      else
      {
        while(wait(&stat)!=pid);
        close(filedes[1]);
        fd_in = filedes[0];
      }
    i++;
  }
  return ;
}

void parseinput(char *input)
{
  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2, *command[200]={NULL};
  int redirect,flag,i,j,len;
  for (j = 1, str1 = input; ; j++, str1 = NULL) {
  token = strtok_r(str1, ";", &saveptr1);
  if (token == NULL)
    break;
  redirect = 0;
  for(int k = 0;k < strlen(token); k++)
    if(token[k] == '>'|| token[k] == '<'|| token[k] == '|')
      redirect = 1;
  if(redirect)
    redirect_pipe(token);
  else{
    str2 = token; len = 0;
    subtoken = strtok_r(str2, " ", &saveptr2);
    command[len++] = subtoken;
    str2 = NULL;
    flag = 0;
    char arg[200]={'\0'},argument[200]={'\0'};
    for (i = 0; ;i++, str2 = NULL) {
      subtoken = strtok_r(str2, " ", &saveptr2);
      if (subtoken == NULL) break;
      if(!strcmp(command[0],"echo")){
        strcat(argument,subtoken);
        strcat(argument," ");
      }
      else {
        strcat(argument,subtoken);
        command[len++] = subtoken;
        }
      }
    process(command,argument);
    }
  }
}

int child_dir(char *actpath,char *curpath)
{
  int i;
  for(i = 0;i < strlen(actpath);i++)
  if(actpath[i] != curpath[i])
    break;
  return i;
}

int substr(char *actpath,char *curpath)
{
  int i;
  if(strlen(actpath) > strlen(curpath))
    return 0;
  for(i = 0;i < strlen(actpath);i++)
    if(actpath[i] != curpath[i])
      return 0;
  return 1;
}

void getuserdetails(char username[],char pc_name[])
{
  struct passwd *details;
  uid_t user_id;
  char comp_name[100];
  user_id = geteuid();
  details = getpwuid(user_id);
  gethostname(comp_name,100);
  strcpy(username, details->pw_name);
  strcpy(pc_name, comp_name);
}
const char *get_filetype(struct stat *buf)
{
    if(S_ISREG(buf->st_mode))
    {
        return "regular";
    }
    if(S_ISDIR(buf->st_mode))
    {
        return "directory";
    }
    if(S_ISCHR(buf->st_mode))
    {
        return "charater";
    }
    if(S_ISBLK(buf->st_mode))
    {
        return "block";
    }
    if(S_ISFIFO(buf->st_mode))
    {
        return "fifo";
    }   
    return "unknown";
}
int has_apos(char * str)
{
  for(; *str != '\0'; str++)
  {
    if (*str == '\'')
    {
      return 1;
    }
  }
  return 0;
}
void Eliminate(char *str, char ch)
{
    for (; *str != '\0'; str++)
    {
        if (*str == ch)
        {
            strcpy(str, str + 1);
            str--;
        }
    }
}
