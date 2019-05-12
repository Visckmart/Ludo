##################################################
###
### Diretivas de MAKE para o construto: TesteTabuleiro
### Gerado a partir de: TesteTabuleiro.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteTabuleiro


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
   $(Fobj)\tabuleiro.obj   $(Fobj)\circular.obj   $(Fobj)\lista.obj \
   $(Fobj)\jogador.obj   $(Fobj)\testetabuleiro.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\tabuleiro.obj :  {$(Pc)}\tabuleiro.c \
    {$(Ph)}circular.h           {$(Ph)}jogador.h            {$(Ph)}lista.h              \
    {$(Ph)}tabuleiro.h         
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\circular.obj :  {$(Pc)}\circular.c \
    {$(Ph)}circular.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\jogador.obj :  {$(Pc)}\jogador.c \
    {$(Ph)}jogador.h            {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\testetabuleiro.obj :  {$(Pc)}\testetabuleiro.c \
    {$(Ph)}generico.h           {$(Ph)}jogador.h            {$(Ph)}lerparm.h            \
    {$(Ph)}tabuleiro.h          {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\tabuleiro.obj   $(Fobj)\circular.obj   $(Fobj)\lista.obj \
   $(Fobj)\jogador.obj   $(Fobj)\testetabuleiro.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteTabuleiro
###
##################################################

