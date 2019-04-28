ECHO Compila o teste "TesteCircular" gerando TesteCircular.exe como produto
REM Nao esqueca de rodar vsvars32.bat

REM Gera o arquivo make baseado em TesteCircular.comp
pushd .
cd ..\Compilacao\gmake
gmake /b..\ /cTesteCircular
popd

REM Compila o programa baseado nas instrucoes do arquivo make gerado
pushd .
cd..\Compilacao
nmake /FTesteCircular.make

REM Abre o arquivo de erro gerado (feche para continuar)
cd ..\Produto
notepad TesteCircular.err
popd



