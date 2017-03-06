
#include "qu.h"

int qu_matrix[4][3] = {0};

int qu_setQueue(int dir, int floor){

    qu_matrix[dir][floor] = 1;
  return qu_readQueue(dir, floor);


}


int qu_readQueue(int dir, int curr_floor){

  if (dir == 0) {

   for (int i = 0; i < 4; i++) {
     for (int j = 0; j < 3; j++) {
       if (qu_matrix[i][j]==1){
         return j;
       }
       else {
         return -1;
       }
     }
   }
  }

  if (dir == 1) {

     for (int i = curr_floor; i < 4; i++) {
       for (int j = 0; j < 2; j++) {
         if (qu_matrix[i][j]==1){
           return j;
         }
       }
     }

          for (int i = 3; i > -1; i--) {
            for (int j = 0; j < 3; j++) {
              if (qu_matrix[i][j]==1){
               return j;
              }
            }
          }
  }
    if (dir == -1) {

       for (int i = curr_floor; i > -1; i--) {
         for (int j = 1; j < 3; j++) {
           if (qu_matrix[i][j]==1){
             return j;
           }
         }
       }

            for (int i = 0; i < 4; i++) {
              for (int j = 0; j < 3; j++) {
                if (qu_matrix[i][j]==1){
                 return j;
                }
              }
            }

    }

}

void qu_update(int dir, int floor){

  if (dir == -1) {
    qu_matrix[floor][1] = 0;
    qu_matrix[floor][2] = 0;
  }
    else {
      qu_matrix[floor][1] = 0;
      qu_matrix[floor][0] = 0;
    }
}

void qu_deleteQueue(){

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      qu_matrix[i][j] = 0;
    }
  }
}
