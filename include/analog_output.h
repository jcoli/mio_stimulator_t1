/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __ANA_OUTPUT_H__
#define __ANA_OUTPUT_H__ 

void out_ana_begin();
void MCP42010Write(int addr, int pos, int csPin);

#endif