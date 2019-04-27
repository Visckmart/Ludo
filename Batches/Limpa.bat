REM Deleta a compilacao anterior, se existir
pushd .

REM Deletando os arquivos de produto
cd..\Produto
del *.exe
del *.err

REM Deletando os arquivos de objeto
cd ..\Objetos
del *.obj
del *.build

REM Deletando os arquivos de compilacao
cd ..\Compilacao
del *.list
del *.make
popd
