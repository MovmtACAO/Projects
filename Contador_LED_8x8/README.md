
-----

# Contador Numérico em Painel de LED 8x8 NeoPixel

Este é um projeto simples para Arduino que exibe os números de 0 a 9 em um painel de LED 8x8 (64 LEDs WS2812B/NeoPixel). O código inclui uma fonte de bitmap otimizada para clareza e uma função de mapeamento de coordenadas que lida com o layout em "zigue-zague" (serpentina) comum nesses painéis.

## 📖 Visão Geral

O projeto percorre continuamente os números de 0 a 9, exibindo cada um por 3 segundos. A cor, o brilho e a velocidade de exibição podem ser facilmente personalizados no código.

### Exemplo de Saída (Número 8)

```
  . . . . . . . .
  . . █ █ █ █ . .
  . █ . . . . █ .
  . █ . . . . █ .
  . . █ █ █ █ . .
  . █ . . . . █ .
  . █ . . . . █ .
  . . █ █ █ █ . .
```

## ✨ Funcionalidades

  * Exibe os números de 0 a 9 em um loop contínuo.
  * Utiliza uma fonte de bitmap personalizada para representar cada número.
  * Compatível com painéis de LED 8x8 com layout em serpentina.
  * Fácil de modificar cores, brilho e tempo de exibição.

## 🛠️ Componentes Necessários

### Hardware

  * 1x Placa Arduino (Uno, Nano, etc.)
  * 1x Painel de LED 8x8 (64 LEDs endereçáveis WS2812B ou similar)
  * 1x Fonte de alimentação externa de 5V (Recomendado, veja a nota abaixo)
  * Fios Jumper

### Software

  * [Arduino IDE](https://www.arduino.cc/en/software)
  * Biblioteca **Adafruit NeoPixel**

## 🔌 Montagem e Conexões

1.  **Instale a Biblioteca:**

      * Abra a Arduino IDE.
      * Vá em `Sketch` \> `Include Library` \> `Manage Libraries...`.
      * Procure por "Adafruit NeoPixel" e clique em "Install".

2.  **Conecte os Componentes:**

      * Conecte o **GND** do painel de LED ao **GND** da fonte externa e ao **GND** do Arduino.
      * Conecte o pino **5V** (ou VCC) do painel ao **+5V** da fonte externa.
      * Conecte o pino de dados **DIN** (Data In) do painel ao pino digital **6** do Arduino (conforme definido em `#define PIN 6`).

### Diagrama de Conexão

```
      Fonte Externa 5V
           (+) -------
            |        |
           GND --|---o (5V do Painel)
                 |   |
                 |---o (GND do Painel)
                 |
                 |
Arduino -------- |
 |               |
 o (Pino D6) --- o (DIN do Painel)
 |
 o (GND) --------|
```

## ⚙️ Como o Código Funciona

### `numeros[10][8]`

Esta é a matriz que define a "fonte" dos números. É um array 2D onde cada linha representa um número (de 0 a 9) e cada elemento da linha é um byte (`uint8_t`) que define o padrão de uma linha de 8 pixels do painel.

Por exemplo, para o número 0:
`0b00111100` significa que os LEDs nas posições 2, 3, 4 e 5 da primeira linha estarão acesos.

### `desenhaNumero(const uint8_t bitmap[8])`

Esta função recebe um dos bitmaps da matriz `numeros` e o desenha no painel.

1.  Ela primeiro limpa o painel com `painel.clear()`.
2.  Depois, percorre cada linha (`y`) e cada coluna (`x`) do bitmap.
3.  A operação `(bitmap[y] >> (7 - x)) & 1` verifica se o bit correspondente à coluna `x` na linha `y` é `1`.
4.  Se for `1`, a função chama `converteXYparaIndice(x, y)` para obter o índice correto do LED e o acende com a cor definida.
5.  Ao final, `painel.show()` atualiza o painel de uma só vez.

### `converteXYparaIndice(int x, int y)`

Esta é uma função crucial. A maioria dos painéis 8x8 não é ligada de forma linear (0 a 7, 8 a 15, etc.), mas sim em um padrão de "zigue-zague" (serpentina) para facilitar a fabricação.

  * **Linhas pares (0, 2, 4, 6):** Os LEDs são contados da esquerda para a direita.
  * **Linhas ímpares (1, 3, 5, 7):** Os LEDs são contados da direita para a esquerda.

Esta função faz a conversão matemática para que você possa pensar em termos de coordenadas (x, y) e o LED correto seja aceso.

## 🎨 Como Customizar

  * **Mudar o Pino de Dados:** Altere o valor de `#define PIN 6`.
  * **Ajustar o Brilho:** Mude o valor em `painel.setBrightness(40)`. O valor vai de 0 (desligado) a 255 (máximo).
  * **Mudar a Cor:** Na função `desenhaNumero`, altere os valores RGB em `painel.Color(50, 100, 200)`. Os valores são (Vermelho, Verde, Azul), de 0 a 255 cada.
  * **Alterar o Tempo de Exibição:** Mude o valor em `delay(3000)`. O valor é em milissegundos (3000ms = 3 segundos).
  * **Editar a Fonte:** Modifique os valores binários na matriz `numeros` para criar seus próprios caracteres ou ajustar os existentes.

## 📄 Licença

Este projeto é de código aberto. Sinta-se à vontade para usá-lo e modificá-lo.