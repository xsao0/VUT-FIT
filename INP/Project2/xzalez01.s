; Vernamova sifra na architekture DLX
; jmeno prijmeni login

        .data 0x04          ; zacatek data segmentu v pameti
login:  .asciiz "xzalez01"  ; <-- nahradte vasim loginem
cipher: .space 9 ; sem ukladejte sifrovane znaky (za posledni nezapomente dat 0)

        .align 2            ; dale zarovnavej na ctverice (2^2) bajtu
laddr:  .word login         ; 4B adresa vstupniho textu (pro vypis)
caddr:  .word cipher        ; 4B adresa sifrovaneho retezce (pro vypis)

        .text 0x40          ; adresa zacatku programu v pameti
        .global main        ; 

main:   		
	addi r24, r0, 0
	addi r18, r0, 0
start:	
	lb r29, login(r24)	; nacitava znak loginu

	slti r23, r29, 97 	; ak je znak mensi ako 97 'a', skoci na end
	bnez r23, end
	nop

	sgti r23, r29, 123 	; ak je znak vacsi ako 123 'z', skoci na end
	bnez r23, end
	nop

	beqz r18, key_z		; ak je r18 rovny 0, skoci na key_z
	nop
	
	bnez r18, key_a		; ak je r18 rovny 1, skoci na key_a 
	nop

key_z:				; 'z' posuva o 26 znakov , cize sa dany znak loginu nemeni 
	sb cipher(r24), r29	; uklada znak loginu
	addi r24, r24, 1	; posuva sa v logine na dalsi znak 
	addi r18, r18, 1	; nastavuje hodnotu r 18 na 1
	j start			; vracia sa na start
	nop

key_a:
	subi r29, r29 ,1	; 'a' posuva o 1 znak vzad

	slti r23, r29, 97	; kontrola, ci nie je znak mensi ako 97 'a'
	bnez r23, fix		; ak je znak mensi ako 97 'a', skaci na fix
	nop			; v mojom pripade nenastava pretecenie, ale pre istotu som osetril tuto moznost

	sb cipher(r24), r29	; uklada znak loginu
	addi r24, r24, 1	; posuva sa v logine na dalsi znak 
	addi r18, r0, 0		; nastavuje hodnotu r18 na 0
	j start 		; vracia sa na start
	nop

fix:
	addi r29, r29, 26	; posuva o 26 znakov na koniec abecedy 
	sb cipher(r24), r29	; uklada znak loginu
	addi r24, r24, 1	; posuva sa v logine na dalsi znak 
	addi r18, r0, 0		; nastavuje hodnotu r18 na 0
	j start 		; vracia sa na start
	nop

end:    sb cipher(r24), r0	; pridava na koniec 0
	addi r14, r0, caddr ; <-- pro vypis sifry nahradte laddr adresou caddr
        trap 5  ; vypis textoveho retezce (jeho adresa se ocekava v r14)
        trap 0  ; ukonceni simulace
