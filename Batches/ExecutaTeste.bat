ECHO Executa os testes ja compilados baseado no arquivo TesteSoma.script
pushd .
cd..\Produto
TRAB4-1.exe /s..\Script\TesteCircular.script
TRAB4-2.exe /s..\Script\TesteJogador.script
TRAB4-3.exe /s..\Script\TesteLista.script
TRAB4-4.exe /s..\Script\TesteTabuleiro.script
TRAB4-5.exe /s..\Script\TesteCircularConta.script
notepad ContadoresCircular.txt
popd