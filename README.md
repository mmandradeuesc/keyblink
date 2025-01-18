# EmbarcaTech   
### TAREFA 1 - U4C2O1234A, Unidade 4 - Capítulo 1
#### Grupo 4 - Subgrupo 7
#### Integrantes:
* Marcel Mascarenhas Andrade
* Roberto Vítor Lima Gomes Rodrigues
* Davi Nascimento Leão





#### Instruções de compilação
Ambiente VS Code com o Pico SDK configurado.
CMake e Make instalados.
Simulador Wokwi integrado ao VS Code.
Passos

Clone o repositório:
bash
Copiar
Editar
git clone https://github.com/<usuario>/<repositorio>.git
cd <repositorio>

Crie uma pasta para os arquivos de compilação:
bash
Copiar
Editar
mkdir build
cd build

Configure o projeto com o CMake:
bash
Copiar
Editar
cmake ..

Compile o código:
bash
Copiar
Editar
make

Localize o arquivo .uf2 gerado na pasta build e envie-o para o RP2040:
Conecte o microcontrolador ao computador pressionando o botão BOOTSEL.
Arraste e solte o arquivo .uf2 na unidade montada.

* ##### Alternativamente
Se você preferir simular o projeto sem usar o hardware, siga estes passos:

Abra o projeto no VS Code.
Certifique-se de que a extensão do Wokwi está instalada.
Crie um arquivo project.wokwi.json para definir os componentes simulados.
Execute a simulação clicando em Run ou pressionando F5


Atividade Unidade 4 do Embarcatech

Atividade 1 (Obrigatória): Controle de pinos GPIO com o
emprego de um teclado matricial.
Com o auxílio do simulador de eletrônica Wokwi, utilize um
teclado matricial 4x4 (ilustrado na Figura 1) para controlar
determinados pinos GPIO do microcontrolador RP2040,
presente na placa de desenvolvimento Raspberry Pi Pico W.
Para esta atividade, realize o acionamento de 03 LEDs (tipo
RGB), juntamente com o controle do sinal sonoro de um buzzer.
Nesta prática, será necessário simular os seguintes
componentes:
1) Teclado matricial 4x4.
2) 03 LEDs – tipo RGB.
3) Componente Buzzer.
4) Microcontrolador Raspberry Pi Pico W.
