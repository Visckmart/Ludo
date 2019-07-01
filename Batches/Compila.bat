ECHO Compila o teste "TesteCircular" gerando TesteCircular.exe como produto
REM Nao esqueca de rodar vsvars32.bat

REM Gera o arquivos make baseado nos .comp
pushd .
cd ..\Compilacao\gmake
gmake /b..\ /cTesteCircular
gmake /b..\ /cTesteLista
gmake /b..\ /cTesteCircularConta
gmake /b..\ /cTesteTabuleiro
gmake /b..\ /cTesteJogador
gmake /b..\ /cPartida
popd

REM Compila o programa baseado nas instrucoes dos arquivos make gerado
pushd .
cd..\Compilacao
nmake /FTesteLista.make
del ..\Objetos\*.obj
nmake /FTesteCircular.make
del ..\Objetos\*.obj
nmake /FTesteCircularConta.make
del ..\Objetos\*.obj
nmake /FTesteJogador.make
del ..\Objetos\*.obj
nmake /FTesteTabuleiro.make
del ..\Objetos\*.obj
nmake /FPartida.make
REM Abre os arquivos de erro gerados (feche para continuar)
cd ..\Produto

copy    *.err      Tudo.err
notepad Tudo.err
popd



