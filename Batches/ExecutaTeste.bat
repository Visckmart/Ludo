ECHO Executa os testes ja compilados baseado no arquivo TesteSoma.script
pushd .
cd..\Produto
TesteCircular.exe /s..\Script\TesteCircular.script
TesteLista.exe /s..\Script\TesteLista.script
TesteTabuleiro.exe /s..\Script\TesteTabuleiro.script
popd