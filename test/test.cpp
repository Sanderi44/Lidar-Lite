#include <include/lidar_lite.h>
#include <cstdio>
#include <unistd.h>

int main(){
  Lidar_Lite l1(1);
  int err = l1.connect();
  if (err < 0){
    printf("%d", l1.err);
  } else {
    while(l1.err >= 0){
      int dist = l1.getDistance();
      printf("%d\n", dist);
      usleep(100000);
    }
  }
}
