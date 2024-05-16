;   уравнения кривых - 10

section .data
    const1 dq 1.0
    const2 dq 2.0
    const3 dq 3.0
    const4 dq 4.0
    one dq -1.0
    
section .text

;   f1 = 1 + 4/(x^2 + 1)
global _f1
_f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[const4]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fld1
    faddp
    fdivp
    fld1
    faddp
    leave 
    ret
    
    
    
    
;   f2 = x^3
global _f2
_f2:
    push ebp
    mov ebp, esp; for correct debugging
    SUb esp, 8
    ; x^3
    FINIT
    fld qword[ebp+8] ; загрузка x в стек FPU
    FLD st0
    FMULP  ; ST(1) = ST(0) * ST(1) and pop st0
    FLD qword[ebp+8]
    FMULP
    
    LEAVE
    ret
    
;   f3 = 2^-x
global _f3
_f3:
        push ebp
    mov ebp, esp; for correct debugging
    SUb esp, 4
    FINIT
    
    ;GET THE INTEGER PART
    FLD qword [ebp+8]      ; Load x onto the FPU stack
    FRNDINT                  ; Get the integer part of x in st1 
    
    fld qword[one]
    fmulp; st(1) = -x
    
    FLD1                     ; and one in st0
    FSCALE                   ; ST(0) = ST(0) * 2ST(1) 

    ;GET THE FRACTIONAL PART
    FLD qword[ebp+8]
    FLD st0                  ; Duplicate x
    FRNDINT                  ; Integer part in st0
    FSUBP st1, st0           ; ST(1) = ST(1) - ST(0) and pop integer part
   
    fld qword[one]
    fmulp; st(0) = -x
    
    F2XM1                    ; ST(0) = 2^ST(0) - 1
    FLD1
    FADDP                    ; get 2^x fractional 

    ;COMBINE
    FMULP                    ;ST(1) = ST(0) * ST(1) add pop st0
    leave
    ret
    
    
