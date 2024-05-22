
; MEC - UTFPR - DAELN - Curso Técnico em Eletrônica - Microcontroladores 1 - Prof. Cion - 12 nov 2014

; Programação Assembly 8051
; Este programa classifica uma lista de bytes em ordem crescente, utilizando o algoritmo Insert Sort.
; A lista deve ser armazenada a partir do endereço 10h da RAM e pode conter no máximo 110 bytes (M[10] a M[7eh])

    FimLista equ 7fh ; Endereço do fim da lista
             mov 10h,#5 ; lista a ser classificada, iniciada no endereco M[10h]
             mov 11h,#4 ;
             mov 12h,#3 ;
             mov 13h,#2 ;
             mov 14h,#1 ;
             mov FimLista,#15h ; endereco do fim da lista
             mov r0,#10h ; ponteiro para inicio da lista

      Loop:  mov a,r0
             inc a
             mov r1,a ; faz r1 = r0 + 1 - ponteiro para próximo byte a ser comparado

      Loop2: clr c ; limpa carry devido à SUBB
             mov a,@r0
             subb a,@r1 ; verifica se (M[R0] < M[R1])
             jc N_Troca ; se sim, não troca
             mov a,@r0 ; troca M[R0] com M[R1]
             mov b,@r1
             mov @r0,b
             mov @r1,a

     N_Troca:inc r1 ; incrementa apontador
             mov a,r1
             cjne a,FimLista, Loop2 ; verifica se (R1 == FimLista), se não retorna
             inc r0 ; se sim, move ponteiro para o próximo byte
             mov a,r0
             inc a ; testa ponteiro para um endereço acima
             cjne a,FimLista, Loop ; verifica se lista está classificada. Se não, continua

     Fim:    jmp $ ; Lista classificada, loop infinito