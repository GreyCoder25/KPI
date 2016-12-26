Data1	Segment

var_db          db	1010b
var_dw          dw	2904d
var_dd		dd	384abh
string		db	'autoВаСя'

Data1	ends

Data2	Segment
var_ds2_dw	dw	5844d
Data2	ends

Code1	Segment
        Assume	cs:Code1, ds:Data1, es:Data2
begin:

stc
cld
pop	eax
mul	var_dw
mov	eax, edx
xor	ax, [esi]
xor	eax, [si]
xor	ax, [si]
xor     [eax*2], edx
sbb     var_dd, eax
codeseg1:
xor	al, var_db
@label2:
xor ax, word ptr[ebx]
sub	var_dd, eax
jmp	var_dd
cmp	cx, 5
jnc	@label1
adc	var_dw, 4
adc     es:var_ds2_dw, 4
jnc	@label2
mul	word ptr[eax*2]

@label1:

jmp far ptr codeseg2

Code1 ends
Code2 Segment
        Assume	cs:Code2
        codeseg2:
        jmp far ptr codeseg1
Code2 ends
        end
