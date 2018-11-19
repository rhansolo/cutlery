#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int abuctChild(int i){
  int time = 5 + (i % 16);
  sleep(time);
  if (getppid() != -1){
    printf("Completed child's pid: %d | Asleep for %d seconds\n", getpid(), time);
  }
  return time;
}

int main(){
  srand(time(NULL));
  int arr[2];
  arr[0] = rand();
  arr[1] = rand();
  printf("I'm a parent, my pid is %d\n", getpid());
  int status;
  int pid1 = fork();
  if(pid1 == 0){
    printf("I'm a child, my pid is %d\n", getpid());
    return abuctChild(arr[0]);
  }
  else{
    int pid2 = fork();
    if(pid2 == 0){
      printf("I'm a child, my pid is %d\n", getpid());
      return abuctChild(arr[1]);
    }
    else{
      int cpid = wait(&status);
      printf("Parent waited %d seconds for child %d. So tardy...\n", WEXITSTATUS(status), cpid);
      return 0;
    }
  }
}