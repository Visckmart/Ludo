##################################################
###
### Diretivas de MAKE para o construto: TesteCircular
### Gerado a partir de: TesteCircular.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteCircular


### Nomes de paths

Ph                   = ..\Ludo
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Ludo
Pc                   = ..\Ludo

### Nomes de diretórios para geração

Fh                   = ..\Ludo
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Ludo
Fc                   = ..\Ludo

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\circular.obj   $(Fobj)\testecircular.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\circular.obj :  {$(Pc)}\circular.c \
    {$(Ph)}circular.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testecircular.obj :  {$(Pc)}\testecircular.c \
    {$(Ph)}circular.h           {$(Ph)}generico.h           {$(Ph)}lerparm.h            \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\circular.obj   $(Fobj)\testecircular.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteCircular
###
##################################################

