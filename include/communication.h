/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

void bt_init();
void bt_at_command(String at_comm);
void on_serial();
void on_BT_comm(); 
void sendMsgTimer();
void sendMsg(String s);


#endif
