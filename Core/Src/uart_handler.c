#include "uart_handler.h"
#include "fsm_handler.h"
extern UART_HandleTypeDef huart1;
uint8_t command;
uint8_t num_cmd[10];
uint8_t num_mess[10];
uint8_t recieve;
extern int auto_control_flag;
void print_int(int number){
  int l;
  l = sprintf(num_mess, "\n%d\n", number);
  HAL_UART_Transmit_IT(&huart1, num_mess, l);
}
void handle_command(uint8_t cmd,int number){
  all_handler(cmd, number);
}
int num_ready = 0;
int num_pointer;

/**
* @brief Interpret command as letter and number, if there is no number as argument - can be used instead.
* @param huart 
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if(recieve >= 'a' && recieve <= 'z'){
    num_ready = 1;
    command = recieve;
    num_pointer = 0;
  }
  else if(num_ready && ((recieve >= '0' && recieve <='9') || recieve == '-') && num_pointer < 10){
    num_cmd[num_pointer] = recieve;
    num_pointer++;
  }
  else if(num_pointer > 0 && num_ready == 1){
    num_cmd[num_pointer] = '\0';
    handle_command(command, atoi(num_cmd));
    num_ready = 0;
  }
  else{
    num_ready = 0;
  }
  HAL_UART_Receive_IT(&huart1, &recieve, 1);
}