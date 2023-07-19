## CMakeLists.txt documentation
O código Patricia tem como propósito implementar uma árvore de busca patrícia, também conhecida como trie compacta. Essa estrutura de dados é utilizada para armazenar e pesquisar palavras ou sequências de caracteres de forma eficiente. 

A árvore de busca patrícia é alcançada através da divisão dos caracteres em nós, onde cada nó representa um prefixo comum entre as palavras armazenadas. Isso permite uma busca rápida e eficiente, pois a árvore é construída de forma a minimizar o número de comparações necessárias.

Um detalhe importante é que a árvore de busca patrícia é uma estrutura de dados compacta, pois ela não armazena nós desnecessários. Isso resulta em uma economia de espaço em relação a outras estruturas de dados, como árvores de busca binárias.

No código fornecido, a função add_library(Patricia Patricia.c) adiciona o arquivo Patricia.c à biblioteca Patricia, que provavelmente contém a implementação da árvore de busca patrícia.
## Patricia.c documentation
O código implementa uma árvore Patricia, uma estrutura de dados usada para armazenar e pesquisar palavras. O propósito é permitir a inserção, pesquisa e contagem de nós internos e externos na árvore Patricia.

A árvore Patricia é uma árvore de busca compacta que armazena palavras em nós externos e usa nós internos para representar prefixos comuns entre as palavras. Cada nó interno contém um caractere e um offset, que indica a posição do próximo caractere a ser comparado. Os nós externos contêm as palavras.

A inserção é feita percorrendo a árvore até encontrar um nó externo ou um offset menor que o do nó atual. Em seguida, cria-se um novo nó externo e um novo nó interno para representar o prefixo comum entre a palavra a ser inserida e a palavra existente no nó atual.

A pesquisa é feita percorrendo a árvore até encontrar um nó externo com a palavra desejada. A contagem de nós internos e externos é feita percorrendo a árvore e contando os nós de cada tipo.

Um detalhe importante é que a árvore Patricia é implementada usando ponteiros para nós, permitindo a manipulação eficiente da estrutura.
## Patricia.h documentation
O código implementa uma árvore Patricia, uma estrutura de dados utilizada para armazenar e pesquisar palavras. O propósito do código é fornecer funções para criar, pesquisar e manipular uma árvore Patricia.

A árvore Patricia é uma árvore de busca compacta que armazena palavras em nós internos e externos. Os nós internos contêm um caractere e dois ponteiros para nós filhos, enquanto os nós externos contêm a palavra armazenada. A árvore é construída de forma a minimizar o número de comparações necessárias para pesquisar uma palavra.

O código implementa funções para criar nós internos e externos, pesquisar uma palavra na árvore, inserir uma nova palavra na árvore, calcular a altura da árvore e contar o número de nós na árvore.

Um detalhe importante é que a árvore Patricia é uma estrutura de dados eficiente para armazenar e pesquisar palavras, especialmente quando há muitas palavras com prefixos comuns.
