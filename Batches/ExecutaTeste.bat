ECHO Executa os testes ja compilados baseado no arquivo TesteSoma.script
pushd .
cd..\Produto
TRAB2-1.exe /s..\Script\TesteCircular.script
TesteCircularConta.exe /s..\Script\TesteCircularConta.script
TRAB2-2.exe /s..\Script\TesteJogador.script
TRAB2-3.exe /s..\Script\TesteLista.script
TRAB2-4.exe /s..\Script\TesteTabuleiro.script

popd