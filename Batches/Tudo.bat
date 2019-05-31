ECHO Limpa, compila e executa o programa de testes "TesteSoma"
REM EXECUTE vsvars32.bat ANTES DE RODAR
if not exist ..\Produto\ mkdir ..\Produto\
Call Limpa
Call Compila
Call ExecutaTeste