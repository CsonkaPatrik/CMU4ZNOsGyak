#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
   pid_t  pid;
   int ret = 1;
   int status;
   pid = fork();
        if (pid == -1)
        {
            printf("a gyermek folyamat nem jott letre, hiba tortent\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("a child folyamat pid: %u\n",getpid());
            printf("Child processz\n");
            printf("a child folyamat parent, pid-je: %u\n",getppid());

            execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char *) 0);
        exit(0);
        }
        else
        {
            printf("Parent processz\n");
            printf("a parent folyamat, pid:%u\n",getpid());
            printf("a child folyamat pid: %u\n",pid);

        if (waitpid(pid, &status, 0) > 0)
        {
            if (WIFEXITED(status) && !WEXITSTATUS(status))
              printf("a program vegrehajtasa befejezodott\n");
            else if (WIFEXITED(status) && WEXITSTATUS(status))
            {
                if (WEXITSTATUS(status) == 127)
                {
                    // execlp hiba
                    printf("execl futasi hiba\n");
                }
                else
                    printf("a program normalisan befejezodott,de nem 0 statusszal\n");
            }
            else
               printf("a program nem normalisan ert veget\n");
        }
        else
        {
           // waitpid() hiba
           printf("waitpid() varakozasi hiba\n");
        }
      exit(0);
   }
   return 0;
}