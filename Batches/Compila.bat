ECHO Compila o teste "TesteCircular" gerando TesteCircular.exe como produto
REM Nao esqueca de rodar vsvars32.bat

REM Gera o arquivos make baseado nos .comp
pushd .
cd ..\Compilacao\gmake
gmake /b..\ /cTesteCircular
gmake /b..\ /cTesteLista
popd

REM Compila o programa baseado nas instrucoes dos arquivos make gerado
pushd .
cd..\Compilacao
nmake /FTesteCircular.make
nmake /FTesteLista.make

REM Abre os arquivos de erro gerados (feche para continuar)
cd ..\Produto
notepad TesteCircular.err
notepad TesteLista.err
popd



